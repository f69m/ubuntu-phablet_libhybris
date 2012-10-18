#ifndef UBUNTU_UI_SESSION_SERVICE_H_
#define UBUNTU_UI_SESSION_SERVICE_H_

#include "ubuntu/application/ui/session.h"
#include "ubuntu/platform/shared_ptr.h"

namespace ubuntu
{
namespace application
{
namespace ui
{
class Session;
class SessionCredentials;
}
}
namespace ui
{
class SessionService : public platform::ReferenceCountedBase
{
  public:
    typedef platform::shared_ptr<SessionService> Ptr;

    static const Ptr& instance();

    virtual ~SessionService() {}

    virtual const ubuntu::application::ui::Session::Ptr& start_a_new_session(const ubuntu::application::ui::SessionCredentials& cred) = 0;

  protected:
    SessionService() {}
    SessionService(const SessionService&) = delete;
    SessionService& operator=(const SessionService&) = delete;
};
}
}

#endif // UBUNTU_UI_SESSION_SERVICE_H_
