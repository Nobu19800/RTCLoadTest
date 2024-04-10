// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  RTCLoadTest.cpp
 * @brief RTC startup time measurement Component
 *
 */
// </rtc-template>

#include "RTCLoadTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const rtcloadtest_spec[] =
#else
static const char* rtcloadtest_spec[] =
#endif
  {
    "implementation_id", "RTCLoadTest",
    "type_name",         "RTCLoadTest",
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
RTCLoadTest::RTCLoadTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_testservicePort("testservice")
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTCLoadTest::~RTCLoadTest()
{
}



RTC::ReturnCode_t RTCLoadTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_testservicePort.registerConsumer("testserviceif", "TestService::TimeMeasurement", m_testserviceif);
  
  // Set CORBA Service Ports
  addPort(m_testservicePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTCLoadTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t RTCLoadTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTest::onActivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTest::onExecute(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t RTCLoadTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

RTC::CorbaConsumer<TestService::TimeMeasurement>* RTCLoadTest::getServiceIF()
{
	return &m_testserviceif;
}



extern "C"
{
 
  void RTCLoadTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(rtcloadtest_spec);
    manager->registerFactory(profile,
                             RTC::Create<RTCLoadTest>,
                             RTC::Delete<RTCLoadTest>);
  }
  
}
