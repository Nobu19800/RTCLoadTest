// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file RTCLoadTestComp.cpp
 * @brief Standalone component
 *
 */
// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/ManagerServant.h>
#include <rtm/CORBA_RTCUtil.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "RTCLoadTest.h"

class OverwriteInstanceName
  : public RTM::RtcLifecycleActionListener
{
public:
  OverwriteInstanceName(int argc, char** argv)
    : m_name(""), m_count(0)
  {
    for (size_t i = 0; i < (size_t)argc; ++i)
      {
        std::string opt = argv[i];
        if (opt.find("--instance_name=") == std::string::npos) { continue; }

        coil::replaceString(opt, "--instance_name=", "");
        if (opt.empty()) { continue; }

        m_name = opt;
      }
  }
  virtual ~OverwriteInstanceName() override {}
  virtual void preCreate(std::string& args) override
  {
    if (m_count != 0 || m_name.empty()) { return; }
    args = args + "?instance_name=" + m_name;
    ++m_count;
  }
  virtual void postCreate(RTC::RTObject_impl*) override {}
  virtual void preConfigure(coil::Properties&) override {}
  virtual void postConfigure(coil::Properties&) override {}
  virtual void preInitialize() override {}
  virtual void postInitialize() override {}
private:
  std::string m_name;
  int32_t m_count;
};

void MyModuleInit(RTC::Manager* manager)
{
  RTCLoadTestInit(manager);
  RTC::RtcBase* comp;

  // Create a component
  comp = manager->createComponent("RTCLoadTest");

  if (comp==nullptr)
  {
    std::cerr << "Component create failed." << std::endl;
    abort();
  }

  // Example
  // The following procedure is examples how handle RT-Components.
  // These should not be in this function.

  // Get the component's object reference
//  RTC::RTObject_var rtobj;
//  rtobj = RTC::RTObject::_narrow(manager->getPOA()->servant_to_reference(comp));

  // Get the port list of the component
//  PortServiceList* portlist;
//  portlist = rtobj->get_ports();

  // getting port profiles
//  std::cout << "Number of Ports: ";
//  std::cout << portlist->length() << std::endl << std::endl; 
//  for (CORBA::ULong i(0), n(portlist->length()); i < n; ++i)
//  {
//    PortService_ptr port;
//    port = (*portlist)[i];
//    std::cout << "Port" << i << " (name): ";
//    std::cout << port->get_port_profile()->name << std::endl;
//    
//    RTC::PortInterfaceProfileList iflist;
//    iflist = port->get_port_profile()->interfaces;
//    std::cout << "---interfaces---" << std::endl;
//    for (CORBA::ULong i(0), n(iflist.length()); i < n; ++i)
//    {
//      std::cout << "I/F name: ";
//      std::cout << iflist[i].instance_name << std::endl;
//      std::cout << "I/F type: ";
//      std::cout << iflist[i].type_name << std::endl;
//      const char* pol;
//      pol = iflist[i].polarity == 0 ? "PROVIDED" : "REQUIRED";
//      std::cout << "Polarity: " << pol << std::endl;
//    }
//    std::cout << "---properties---" << std::endl;
//    NVUtil::dump(port->get_port_profile()->properties);
//    std::cout << "----------------" << std::endl << std::endl;
//  }

  return;
}

bool loadTest(std::string lang, RTCLoadTest*rtclt, RTM::ManagerServant* mgrsvt)
{
	RTC::CorbaConsumer<TestService::TimeMeasurement>*serviceIf = rtclt->getServiceIF();

	// If you want to run the manager in non-blocking mode, do like this
	// manager->runManager(true);

	if (lang.empty())
	{
		lang = "C++";
	}

	auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
	auto now_sec = std::chrono::duration_cast<std::chrono::seconds>(now);
	auto now_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now - now_sec);
	std::string command = std::string("RTC:AIST:Test:RTCStartTest:") + lang + std::string(":1.0.0");
	command += "?conf.default.starttime_sec=";
	command += coil::otos(now_sec.count());
	command += "&conf.default.starttime_nsec=";
	command += coil::otos(now_nsec.count());
	//std::cout << __FILE__ << "\t" << __LINE__ << "\t" << now_sec.count() << "\t" << now_nsec.count() << std::endl;
	//RTC::RTObject_var rtcst = mgrsvt.create_component("RTC:AIST:Test:RTCStartTest:C++:1.0.0?starttime_sec=10000000&starttime_nsec=2000000");
	RTC::RTObject_var rtcst = mgrsvt->create_component(command.c_str());

	if (CORBA::is_nil(rtcst.in()))
	{
		std::cout << __FILE__ << "\t" << __LINE__ << ":error" << std::endl;
		return false;
	}

	CORBA_RTCUtil::activate(rtcst.in());
	std::string port0_name = std::string(rtclt->getInstanceName()) + std::string(".testservice");
	RTC::PortService_var port0 = CORBA_RTCUtil::get_port_by_name(rtclt->getObjRef(), port0_name);

	if (CORBA::is_nil(port0.in()))
	{
		std::cout << __FILE__ << "\t" << __LINE__ << ":error" << std::endl;
		return false;
	}

	std::string port1_name = std::string(rtcst->get_component_profile()->instance_name) + std::string(".testservice");
	RTC::PortService_var port1 = CORBA_RTCUtil::get_port_by_name(rtcst.inout(), port1_name);

	if (CORBA::is_nil(port1.in()))
	{
		std::cout << __FILE__ << "\t" << __LINE__ << ":error" << std::endl; std::cout << "error4" << std::endl;
		return false;
	}

	coil::Properties prop;
	CORBA_RTCUtil::connect("testconnector", prop, port0.in(), port1.in());

	try
	{
		RTC::Time diff = serviceIf->_ptr()->getTime();
		double diff_time = static_cast<double>(diff.sec) + static_cast<double>(diff.nsec) * 1.0e-9;
		std::cout << diff_time << std::endl;
	}
	catch (...)
	{

	}
	//rtcst->exit();

	RTM::ManagerList_var mgrlist = mgrsvt->get_slave_managers();
	unsigned int len = mgrlist->length();
	for (unsigned int i = 0; i < len; i++)
	{
		try
		{
			mgrlist[i]->shutdown();
		}
		catch (...)
		{
			std::cout << __FILE__ << "\t" << __LINE__ << std::endl;
		}
	}

	return true;
}

int main (int argc, char** argv)
{
  RTC::Manager* manager;
  manager = RTC::Manager::init(argc, argv);
  manager->addRtcLifecycleActionListener(new OverwriteInstanceName(argc, argv), true);

  // Set module initialization proceduer
  // This procedure will be invoked in activateManager() function.
  manager->setModuleInitProc(MyModuleInit);

  // Activate manager and register to naming service
  manager->activateManager();

  // run the manager in blocking mode
  // runManager(false) is the default.
  manager->runManager(true);

	RTC::RtcBase* comp = manager->getComponent("RTCLoadTest0");

	if (comp == nullptr)
	{
		std::cout << __FILE__ << "\t" << __LINE__ << ":error" << std::endl;
		manager->terminate();
		manager->join();
		return 1;
	}

	RTCLoadTest* rtclt = dynamic_cast<RTCLoadTest*>(comp);
	
	if (rtclt == nullptr)
	{
		std::cout << __FILE__ << "\t" << __LINE__ << ":error" << std::endl;
		manager->terminate();
		manager->join();
		return 1;
	}

	CORBA_RTCUtil::activate(rtclt->getObjRef());

	RTM::ManagerServant& mgrsvt = manager->getManagerServant();
	
	for (int i = 0; i < 10; i++)
	{
		if (!loadTest(manager->getConfig()["RTCStartTest.language"], rtclt, &mgrsvt))
		{
			manager->terminate();
			manager->join();
			return 1;
		}
		
	}

	manager->terminate();
	manager->join();

  return 0;
}
