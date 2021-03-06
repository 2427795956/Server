//@author Jingyu Tong
//@email: jingyutong0806@gmail.com

#ifndef EPOLL_H_
#define EPOLL_H_

#include "Channel.h"
#include "base/noncopyable.h"

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <memory>

class EventLoop;
class Channel;

class Epoll : noncopyable
{
    public:
        typedef std::vector<epoll_event> EventList;
        typedef std::map<int, Channel*> ChannelMap;
        typedef Channel* ChannelPtr;
        
        Epoll(EventLoop* loop);
        ~Epoll();

        void epollAdd(ChannelPtr request); //注册新描述符
        void epollMod(ChannelPtr request); //修改描述符
        void epollDel(ChannelPtr request); //删除描述符
        void updateChannel(ChannelPtr request);  //更新描述符

        std::vector<ChannelPtr>  poll(int timeoutMs); //poll
        std::vector<ChannelPtr> getActiveChannels(int num_events); //返回活动channel的列表，内部使用


    private:
        static const int kInitEventListSize = 16; //初始等待事件个数，可更改
        EventLoop* ownerloop_; //归属loop
        EventList events_; //关心事件，采用vector，自动增长
        ChannelMap fd_to_channel_; //fd转换为Channel
        int epollfd_; //epoll描述符
};






#endif