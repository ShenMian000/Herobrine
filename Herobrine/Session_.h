#ifndef __CLY_SESSION_H__
#define __CLY_SESSION_H__

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#define REPLY_SIZE (32)

// 会话类
class Session_ : public boost::enable_shared_from_this<Session_>
{

public:
	typedef void pSessionCallback(std::string, std::string);

public:
	Session_(boost::asio::io_service& _ioService);
	virtual ~Session_(void);

	void start(void);

	void setCallback(pSessionCallback* _callback)
	{
		callback_ = _callback;
	}

	// socket 实例
	boost::asio::ip::tcp::socket& socket(void);

private:
	// 第一个协议包
	void init_handler(const boost::system::error_code& _error);

	// 解析协议包
	void analyse_handler(const boost::system::error_code& _error);

	// 完成数据传输后触发的收尾工作
	void done_handler(const boost::system::error_code& _error);

	// 读取成功后触发的函数
	void read_handler(const boost::system::error_code& _error, size_t _readSize);

	// 写入完成后触发的函数
	void write_handler(const boost::system::error_code& _error);

private:
	// 临时信息缓冲区
	char				msg_[1024];
	std::string currentMsg_;
	// 数据总数量
	int sumSize_;
	// 单个数据包大小
	unsigned int maxSize_;
	// socket句柄
	boost::asio::ip::tcp::socket socket_;
	// 回调
	pSessionCallback* callback_;
};


#endif // __CLY_SESSION_H__