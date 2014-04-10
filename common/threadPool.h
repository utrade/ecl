/*******************************************************************************
 * Create a boost thread pool                                                  *
 * Copy pasted from                                                            *
 * http://thisthread.blogspot.co.il/2011/04/multithreading-with-asio.html      *

 void run(int tNumber) // 1
 {
   boost::asio::io_service svc; // 2
   boost::asio::io_service::work work(svc); // 3
   boost::thread_group threads;

   for(int i = 0; i < tNumber; ++i) // 4
     threads.create_thread(std::bind(&boost::asio::io_service::run, &svc));

   svc.post(std::bind(jobOne, 2)); // 5
   svc.post(std::bind(jobOne, 1));
   svc.post(std::bind(jobTwo, 500));
  
   svc.stop(); // 6
   threads.join_all(); // 7
 }
 ******************************************************************************/

#ifndef UT_THREAD_POOL_H
#define UT_THREAD_POOL_H

#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

/*******************************************************************************
* To use this thread pool                                                      *
* ThreadPool t( 5 )                                                            *
* t.post( boost::bind( &ClassName::MethodName, &Object ) )                     *
* i.e. Address of the method & reference to the object                         *
*******************************************************************************/
namespace UT 
{
  class ThreadPool
  {
    public :
      ThreadPool( int noOfThreads = 1) ;
      ~ThreadPool() ;

      template< class func >
        void post( func f ) ;

      boost::asio::io_service &getIoService() ;

    private :
      boost::asio::io_service _ioService; 
      boost::asio::io_service::work _work ;
      boost::thread_group _threads;
  };

  inline ThreadPool::ThreadPool( int noOfThreads ) 
    : _work( _ioService )
  {
   for(int i = 0; i < noOfThreads ; ++i) // 4
     _threads.create_thread(
         boost::bind(&boost::asio::io_service::run, &_ioService));
  }

  inline ThreadPool::~ThreadPool() 
  {
    _ioService.stop() ;
    _threads.join_all() ;
  }

  inline boost::asio::io_service &ThreadPool::getIoService() 
  {
    return _ioService ;
  }

  template< class func >
    void ThreadPool::post( func f ) 
    {
      _ioService.post( f ) ;
    }
}

#endif 
