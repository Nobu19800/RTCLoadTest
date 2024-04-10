// -*-C++-*-
/*!
 * @file  TestServiceSVC_impl.cpp
 * @brief Service implementation code of TestService.idl (test code)
 *
 */

#include "TestServiceSVC_impl.h"

/*
 * Example implementational code for IDL interface TestService::TimeMeasurement
 */
TestService_TimeMeasurementSVC_impl::TestService_TimeMeasurementSVC_impl()
{
  // Please add extra constructor code here.
}


TestService_TimeMeasurementSVC_impl::~TestService_TimeMeasurementSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
RTC::Time TestService_TimeMeasurementSVC_impl::getTime()
{
	RTC::Time result;
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <RTC::Time TestService_TimeMeasurementSVC_impl::getTime()>"
#endif
  return result;
}



// End of example implementational code



