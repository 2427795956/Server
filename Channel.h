//@author Jingyu Tong
//@email: jingyutong0806@gmail.com

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "base/noncopyable.h"
#include "EventLoop.h"

#include <functional>

class EventLoop;

//用于IO事件分发
//一个Channel负责一个fd
    
class Channel : noncopyable
{
    public:
        typedef std::function<void()> CallBack;

        Channel(EventLoop* loop, int fd);
        ~Channel();
        //注册读写错误回调
        void setReadCallback(CallBack rh) {
            readHandler_ = std::move(rh);            
        }
        void setWriteCallback(CallBack wh) {
           writeHandler_ = std::move(wh); 
        }
        void setErrorCallback(CallBack eh) {
            errorHandler_ = std::move(eh);
        }
        void setCloseCallback(CallBack cb) {
            closeHandler_ = std::move(cb);
        }
        //开关事件，并更新poller等待的相应事件
        void enableReading() { events_ |= kReadEvent; update(); }
        void disableReading() { events_ &= ~kReadEvent; update(); }
        void enableWriting() { events_ |= kWriteEvent; update(); }
        void disableWriting() { events_ &= ~kWriteEvent; update(); }
        void disableAll() { events_ = kNoneEvent; update(); }

        void handleEvent(); //事件处理

        void setRevents(int revents)
        { revents_ = revents; }
        void setEvents(int events)
        { events_ = events; }

        //返回channel负责的描述符
        int getFd() const 
        { return fd_; }
        //返回events
        int getEvents() const 
        { return events_; }
        int getRevents() const 
        { return revents_; }

        //判断写事件是否已经开启，减少一次update
        bool isWriting() const 
        {return events_ & kWriteEvent; }

        //将Channel加入reacotr
        void update();
        
        static const int kNoneEvent;
        static const int kReadEvent;
        static const int kWriteEvent;
    
    private:
        EventLoop* loop_; //属于的reactor
        const int fd_; //负责的fd
        int events_; //poll/epoll关心的事件
        int revents_; //活动事件
        bool event_handleing_;
        CallBack readHandler_;
        CallBack writeHandler_;
        CallBack errorHandler_;
        CallBack closeHandler_;
};




#endif