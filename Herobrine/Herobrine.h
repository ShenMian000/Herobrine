
#include "Session.h"

class Herobrine : public Session
{
public:
	Herobrine(boost::asio::io_context&, const std::string&, unsigned short);

protected:
	void OnConnect(const boost::system::error_code&) override;
	void OnRead(const boost::system::error_code&, size_t) override;
};
