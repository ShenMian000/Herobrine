
#include <string>
#include <boost/asio.hpp>

class Session
{
public:
	void run();

protected:
	Session(const std::string&, unsigned short);
	~Session();

	void Connect();
	void Send(const std::string&);
	void Recv(std::string&);

	virtual void OnConnect(const boost::system::error_code&);
	virtual void OnSend(const boost::system::error_code&, size_t);
	virtual void OnRecv();

private:
	boost::asio::io_service				 ios;
	boost::asio::ip::tcp::endpoint endpoint;
	boost::asio::ip::tcp::socket	 sock;
};
