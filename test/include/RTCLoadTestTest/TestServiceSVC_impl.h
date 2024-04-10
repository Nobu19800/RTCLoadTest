// -*-C++-*-
/*!
 * @file  TestServiceSVC_impl.h
 * @brief Service implementation header of TestService.idl (test code)
 *
 */

#include "BasicDataTypeSkel.h"

#include "TestServiceSkel.h"

#ifndef TESTSERVICESVC_IMPL_H
#define TESTSERVICESVC_IMPL_H
 
/*!
 * @class TestService_TimeMeasurementSVC_impl
 * Example class implementing IDL interface TestService::TimeMeasurement
 */
class TestService_TimeMeasurementSVC_impl
 : public virtual POA_TestService::TimeMeasurement,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~TestService_TimeMeasurementSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
   TestService_TimeMeasurementSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~TestService_TimeMeasurementSVC_impl();

   // attributes and operations
   RTC::Time getTime();

};



#endif // TESTSERVICESVC_IMPL_H


