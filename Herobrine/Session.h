
#include <string>
#include <boost/asio.hpp>



class Session
{
protected:
	Session(boost::asio::io_context&, const std::string&, unsigned short);
	~Session();

	void Connect();
	void Write(const std::string&);
	void Read();

	virtual void OnConnect(const boost::system::error_code&);
	virtual void OnWrite(const boost::system::error_code&);
	virtual void OnRead(const boost::system::error_code&, size_t);
	
	char buffer[1024];

private:
	boost::asio::ip::tcp::endpoint endpoint;
	boost::asio::ip::tcp::socket	 sock;
};
