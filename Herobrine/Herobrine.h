
#include "Session.h"

class Herobrine : public Session
{
public:
	Herobrine(const std::string&, unsigned short);

protected:
	void OnConnect(const boost::system::error_code&) override;

private:
	void main();
};
