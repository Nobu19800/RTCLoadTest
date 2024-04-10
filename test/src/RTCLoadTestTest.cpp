// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  RTCLoadTestTest.cpp
 * @brief RTC startup time measurement Component (test code)
 *
 */
// </rtc-template>

#include "RTCLoadTestTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const rtcloadtest_spec[] =
#else
static const char* rtcloadtest_spec[] =
#endif
  {
    "implementation_id", "RTCLoadTestTest",
    "type_name",         "RTCLoadTestTest",
    "description",       "RTC startup time measurement Component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Test",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTCLoadTestTest::RTCLoadTestTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_testservicePort("testservice")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTCLoadTestTest::~RTCLoadTestTest()
{
}



RTC::ReturnCode_t RTCLoadTestTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_testservicePort.registerProvider("testserviceif", "TestService::TimeMeasurement", m_testserviceif);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_testservicePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTCLoadTestTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t RTCLoadTestTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTestTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTestTest::onActivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTestTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTestTest::onExecute(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTestTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTestTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTestTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTestTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTestTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool RTCLoadTestTest::runTest()
{
    return true;
}


extern "C"
{
 
  void RTCLoadTestTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(rtcloadtest_spec);
    manager->registerFactory(profile,
                             RTC::Create<RTCLoadTestTest>,
                             RTC::Delete<RTCLoadTestTest>);
  }
  
}
