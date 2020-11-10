#ifdef _WIN32
#include <windows.h>
#endif

#include "gl.h"
#include "glu.h"

// We include these files from modeler so that we can
// display the rendered image in OpenGL -- for debugging
// purposes.

#include "ModelerCamera.h"

#pragma warning(push)
#pragma warning(disable : 4244)

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502f
#endif 
namespace disc0ver {
	const double kMouseRotationSensitivity = 1.0f / 90.0f;
	const double kMouseTranslationXSensitivity = 0.03f;
	const double kMouseTranslationYSensitivity = 0.03f;
	const double kMouseZoomSensitivity = 0.08f;

	void ModelerCamera::calculateViewingTransformParameters()
	{
		Mat4f dollyXform;
		Mat4f azimXform;
		Mat4f elevXform;
		Mat4f twistXform;
		Mat4f originXform;

		vec3<TRANSFORM> upVector;

		makeHTrans(dollyXform, Vec3f(0, 0, mDolly));
		makeHRotY(azimXform, (float)mAzimuth);
		makeHRotX(elevXform, (float)mElevation);
		makeDiagonal(twistXform, 1.0f);
		makeHTrans(originXform, Vec3f(mLookAt.x, mLookAt.y, mLookAt.z));

		mPosition = Vec3f(0, 0, 0);
		// grouped for (mat4 * vec3) ops instead of (mat4 * mat4) ops
		mPosition = originXform * (azimXform * (elevXform * (dollyXform * Vec3f(mPosition.x, mPosition.y, mPosition.z))));

		if (fmod((double)mElevation, 2.0f * M_PI) < 3 * M_PI / 2 && fmod((double)mElevation, 2.0f * M_PI) > M_PI / 2)
			mUpVector = vec3<TRANSFORM>(0, -1, 0);
		else
			mUpVector = vec3<TRANSFORM>(0, 1, 0);

		mDirtyTransform = false;
	}

	ModelerCamera::ModelerCamera()
	{
		reset();
	}

	void ModelerCamera::reset()
	{
		mElevation = mAzimuth = mTwist = 0.0f;
		mDolly = -20.0f;
		mElevation = 0.2f;
		mAzimuth = (double)M_PI;

		mLookAt = vec3<TRANSFORM>(0, 0, 0);
		mCurrentMouseAction = kActionNone;

		calculateViewingTransformParameters();
	}

	void ModelerCamera::clickMouse(MouseAction_t action, int x, int y)
	{
		mCurrentMouseAction = action;
		mLastMousePosition[0] = x;
		mLastMousePosition[1] = y;
	}

	void ModelerCamera::dragMouse(int x, int y)
	{
		vec3<TRANSFORM> mouseDelta = vec3<TRANSFORM>(x, y, 0.0f) - mLastMousePosition;
		mLastMousePosition = vec3<TRANSFORM>(x, y, 0.0f);

		switch (mCurrentMouseAction)
		{
		case kActionTranslate:
		{
			calculateViewingTransformParameters();

			double xTrack = -mouseDelta[0] * kMouseTranslationXSensitivity;
			double yTrack = mouseDelta[1] * kMouseTranslationYSensitivity;

			vec3<TRANSFORM> transXAxis = cross(mUpVector, (mPosition - mLookAt));
			transXAxis /= sqrt(dot(transXAxis, transXAxis));
			vec3<TRANSFORM> transYAxis = cross((mPosition - mLookAt), transXAxis);
			transYAxis /= sqrt(dot(transYAxis, transYAxis));

			setLookAt(getLookAt() + transXAxis * xTrack + transYAxis * yTrack);

			break;
		}
		case kActionRotate:
		{
			double dAzimuth = -mouseDelta[0] * kMouseRotationSensitivity;
			double dElevation = mouseDelta[1] * kMouseRotationSensitivity;

			setAzimuth(getAzimuth() + dAzimuth);
			setElevation(getElevation() + dElevation);

			break;
		}
		case kActionZoom:
		{
			double dDolly = -mouseDelta[1] * kMouseZoomSensitivity;
			setDolly(getDolly() + dDolly);
			break;
		}
		case kActionTwist:
			// Not implemented
		default:
			break;
		}

	}

	void ModelerCamera::releaseMouse(int x, int y)
	{
		mCurrentMouseAction = kActionNone;
	}


	void ModelerCamera::applyViewingTransform() {
		if (mDirtyTransform)
			calculateViewingTransformParameters();

		// Place the ModelerCamera at mPosition, aim the ModelerCamera at
		// mLookAt, and twist the ModelerCamera such that mUpVector is up
		gluLookAt(mPosition[0], mPosition[1], mPosition[2],
			mLookAt[0], mLookAt[1], mLookAt[2],
			mUpVector[0], mUpVector[1], mUpVector[2]);

		// Depending on which class you're in, you may have to 
		// implement this yourself!
	}

	void ModelerCamera::lookAt(vec3<TRANSFORM> eye, vec3<TRANSFORM> at, vec3<TRANSFORM> up)
	{
	}
}


#pragma warning(pop)
