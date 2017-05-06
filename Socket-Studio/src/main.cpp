//
//  sio_test_sample.cpp
//
//  Created by Melo Yao on 3/24/15.
//

#include <sio_client.h>

#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

#ifdef WIN32
#define HIGHLIGHT(__O__) std::cout<<__O__<<std::endl
#define EM(__O__) std::cout<<__O__<<std::endl

#include <stdio.h>
#include <tchar.h>
#else
#define HIGHLIGHT(__O__) std::cout<<"\e[1;31m"<<__O__<<"\e[0m"<<std::endl
#define EM(__O__) std::cout<<"\e[1;30;1m"<<__O__<<"\e[0m"<<std::endl

#define MAIN_FUNC int main(int argc ,const char* args[])
#endif

using namespace sio;
using namespace std;
std::mutex _lock;

std::condition_variable_any _cond;
int my_id;
bool connect_finish = false;

class connection_listener
{
    sio::client &handler;

public:

    connection_listener(sio::client& h):
    handler(h)
    {
    }


    void on_connected()
    {
        _lock.lock();
        _cond.notify_all();
        connect_finish = true;
        _lock.unlock();
    }
    void on_close(client::close_reason const& reason)
    {
        std::cout << "sio closed: " << reason << std::endl;
        exit(0);
    }

    void on_fail()
    {
        std::cout << "sio failed: " <<std::endl;
        exit(0);
    }
};

int participants = -1;

socket::ptr current_socket;

void bind_events(socket::ptr &socket)
{
  (void)socket;
	current_socket->on("test", sio::socket::event_listener_aux([&](string const& name,
                                                            message::ptr const& data,
                                                            bool isAck,message::list &ack_resp)
                       {
                         (void)name;
                         (void)isAck;
                         (void)ack_resp;
                           _lock.lock();
                           if (data->get_map()["send_by"]->get_int() != my_id)
                              std::cout <<  data->get_map()["message"]->get_string() << '\n';
                           _lock.unlock();
                       }));
}

int main()
{

    sio::client h;
    connection_listener l(h);
    std::srand(std::time(0));
    my_id = std::rand();

    h.set_open_listener(std::bind(&connection_listener::on_connected, &l));
    h.set_close_listener(std::bind(&connection_listener::on_close, &l,std::placeholders::_1));
    h.set_fail_listener(std::bind(&connection_listener::on_fail, &l));
    h.connect("http://127.0.0.1:3000");
    _lock.lock();
    if(!connect_finish)
    {
        _cond.wait(_lock);
    }
    _lock.unlock();
		current_socket = h.socket();
    bind_events(current_socket);


        std::string line;

        while (getline(cin, line))
        {
          std::string st("{\"message\": \"" + line  +"\", \"send_by\": " + std::to_string(my_id) + "}");
          current_socket->emit("test", st);
        }

    _lock.lock();
    _cond.wait(_lock);
    _lock.unlock();




    HIGHLIGHT("Closing...");
    h.sync_close();
    h.clear_con_listeners();
	return 0;
}
