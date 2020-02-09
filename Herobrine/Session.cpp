#include <boost/bind.hpp>

#include "Session.h"


Session::Session(boost::asio::io_service& _ioService)
		: socket_(_ioService)
{
	memset(msg_, 0, sizeof(msg_));
}


Session::~Session(void)
{
}


void Session::start(void)
{
	// 告诉链接成功的客户端，你想要的信息。
	char msg[256] = "001:Connect Succeed! Please tell me with 10 bytes, the total data and the size of each package, example:128 1024";
	boost::asio::async_write(socket_, boost::asio::buffer(msg, strlen(msg)),
													 boost::bind(&Session::init_handler, shared_from_this(),
																			 boost::asio::placeholders::error));
}

boost::asio::ip::tcp::socket& Session::socket(void)
{
	return socket_;
}


// 第一个协议包
void Session::init_handler(const boost::system::error_code& _error)
{
	if(_error)
	{
		return;
	}
	// 读取客户端发来的 10 bytes，确定单个包的大小以及数据总大小
	boost::asio::async_read(socket_, boost::asio::buffer(msg_, 10),
													boost::bind(&Session::analyse_handler, shared_from_this(),
																			boost::asio::placeholders::error));
}

void Session::analyse_handler(const boost::system::error_code& _error)
{
	if(_error)
	{
		return;
	}
	// 分析协议包格式
	bool bflag = true;
	// 正则分析格式

	// do something.
	if(!bflag)
	{
		start();
		return;
	}

	// 格式化保存协议包数据
	std::stringstream io(msg_);
	io >> maxSize_;
	io >> sumSize_;

	// 发送接收请求信息
	char msg[REPLY_SIZE];
	sprintf_s(msg, "001:is ok, data remaining %d.", sumSize_);
	boost::asio::async_write(socket_, boost::asio::buffer(msg, REPLY_SIZE),
													 boost::bind(&Session::write_handler, shared_from_this(),
																			 boost::asio::placeholders::error));
}


// 完成数据传输
void Session::done_handler(const boost::system::error_code& _error)
{
	if(_error)
	{
		return;
	}
	currentMsg_ += msg_;
	// 发送信息到回调
	if(!currentMsg_.empty() && callback_ != nullptr)
	{
		callback_(socket_.remote_endpoint().address().to_string(), currentMsg_);
		currentMsg_.clear();
	}
	memset(msg_, 0, sizeof(msg_));

	char msg[32] = "001:will done.";
	boost::asio::async_write(socket_, boost::asio::buffer(msg, REPLY_SIZE),
													 boost::bind(&Session::init_handler, shared_from_this(),
																			 boost::asio::placeholders::error));
}

void Session::read_handler(const boost::system::error_code& _error, size_t _readSize)
{
	if(_error)
	{
		return;
	}
	// 数据处理
	currentMsg_ += msg_;
	if(currentMsg_.size() > 1024 * 512)
	{
		// 发送信息到回调
		if(callback_ != nullptr)
		{
			callback_(socket_.remote_endpoint().address().to_string(), currentMsg_);
			currentMsg_.clear();
		}
	}
	memset(msg_, 0, sizeof(msg_));

	// 计算当前剩余数据数量
	sumSize_ -= _readSize;

	// 接收完成
	if(0 > sumSize_)
	{
		done_handler(_error);
	}
	// 继续接收
	else
	{
		char msg[REPLY_SIZE];
		sprintf_s(msg, "001:%d.", sumSize_);
		boost::asio::async_write(socket_, boost::asio::buffer(msg, REPLY_SIZE),
														 boost::bind(&Session::write_handler, shared_from_this(),
																				 boost::asio::placeholders::error));

		std::cout << "send client recv succeed: " << msg << std::endl;
	}
}
void Session::write_handler(const boost::system::error_code& _error)
{
	if(_error)
	{
		return;
	}

	boost::asio::async_read(socket_, boost::asio::buffer(msg_, maxSize_),
													boost::bind(&Session::read_handler, shared_from_this(),
																			boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}