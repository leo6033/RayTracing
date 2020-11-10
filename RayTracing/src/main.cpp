/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-10-27
 */

#include "ui/GraphicalUI.h"
#include "RayTracer.h"

int main() {
	disc0ver::TraceUI* traceUI = new disc0ver::GraphicalUI();
	disc0ver::RayTracer* theRayTracer = new disc0ver::RayTracer();

	traceUI->setRayTracer(theRayTracer);
    return traceUI->run();
}