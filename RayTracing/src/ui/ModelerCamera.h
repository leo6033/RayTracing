// This ModelerCamera stuff mostly by ehsu

#ifndef ModelerCamera_H
#define ModelerCamera_H

#include "../vecmath/DGM.h"
#include "../vecmath/mat.h"
#include "../vecmath/vec.h"

namespace disc0ver {
    //==========[ class ModelerCamera ]===================================================
    typedef enum { kActionNone, kActionTranslate, kActionRotate, kActionZoom, kActionTwist, } MouseAction_t;

    class ModelerCamera {

    protected:

        double		mElevation;
        double		mAzimuth;
        double		mDolly;
        double		mTwist; // Not implemented yet

        vec3<TRANSFORM>		mLookAt;

        Position		mPosition;
        vec3<TRANSFORM>		mUpVector;
        bool		mDirtyTransform;

        void calculateViewingTransformParameters();

        vec3<TRANSFORM>			mLastMousePosition;
        MouseAction_t	mCurrentMouseAction;


    public:

        //---[ Constructors ]----------------------------------

        // defaults to (0,0,0) facing down negative z axis
        ModelerCamera();
        void reset();

        //---[ Settings ]--------------------------------------

        inline void setElevation(double elevation)
        {
            // don't want elevation to be negative
            if (elevation < 0) elevation += 6.28318530717f;
            mElevation = elevation; mDirtyTransform = true;
        }
        inline double getElevation() const
        {
            return mElevation;
        }

        inline void setAzimuth(double azimuth)
        {
            mAzimuth = azimuth; mDirtyTransform = true;
        }
        inline double getAzimuth() const
        {
            return mAzimuth;
        }

        inline void setDolly(double dolly)
        {
            mDolly = dolly; mDirtyTransform = true;
        }
        inline double getDolly() const
        {
            return mDolly;
        }

        inline void setTwist(double twist)
        {
            mTwist = twist; mDirtyTransform = true;
        }
        inline double getTwist() const
        {
            return mTwist;
        }

        inline void setLookAt(const vec3<TRANSFORM>& lookAt)
        {
            mLookAt = lookAt; mDirtyTransform = true;
        }
        inline vec3<TRANSFORM> getLookAt() const
        {
            return mLookAt;
        }

        //---[ Interactive Adjustment ]------------------------
        // these should be used from a mouse event handling routine that calls
        // the startX method on a mouse down, updateX on mouse move and finally
        // endX on mouse up.
        //-----------------------------------------------------
        void clickMouse(MouseAction_t action, int x, int y);
        void dragMouse(int x, int y);
        void releaseMouse(int x, int y);

        //---[ Viewing Transform ]--------------------------------
        void applyViewingTransform();

        // gluLookAt equivalent
        void lookAt(vec3<TRANSFORM> eye, vec3<TRANSFORM> at, vec3<TRANSFORM> up);
    };
}


#endif
