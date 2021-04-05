#include <coroutine>
#include <iostream>

class MyGenerator {
public:
  struct MyPromise;
  using promise_type = MyPromise;

  MyGenerator(std::coroutine_handle<MyPromise> h)
  : coro_(h) {
    std::cout << "MyGenerator::MyGenerator with coroutine_handle " << h.address() << std::endl;
  }

  ~MyGenerator() {
    std::cout << "MyGenerator::~MyGenerator" << std::endl;
    if(coro_) {
      std::cout << "coroutine " << coro_.address() << " present, calling destroy" << std::endl;
      coro_.destroy();
      std::cout << "coroutine destroyed" << std::endl;
    }
  }

  int very_custom_value() {
    std::cout << "MyGenerator::very_custom_value";
    int promise_val = coro_.promise().get_very_custom_val();
    return promise_val + 1;
  }

  bool very_custom_next() {
    std::cout << "MyGenerator::very_custom_next, calling coro_.resume();" << std::endl;
    coro_.resume();
    
    bool ret = !coro_.done();
    std::cout << "MyGenerator::very_custom_next, coro_.resume() returned, coro_.done = " << !ret << std::endl;
    return ret;
  }

  class MyPromise {
  public:
    struct MyAwaitable {
      bool await_ready() noexcept {
        std::cout << "MyPromise::MyAwaitable::await_ready" << std::endl;
        return false;
      }
      void await_suspend(std::coroutine_handle<MyPromise> h) noexcept {
        std::cout << "MyPromise::MyAwaitable::await_suspend, h = " << h.address() << std::endl;
      }
      void await_resume() noexcept {
        std::cout << "MyPromise::MyAwaitable::await_resume" << std::endl;
      }
    };
    
    MyPromise() {
      std::cout << "MyPromise::MyPromise" << std::endl;
    }
    
    ~MyPromise() {
      std::cout << "MyPromise::~MyPromise" << std::endl;
    }
  
    MyGenerator get_return_object() {
      std::cout << "MyPromise::get_return_object" << std::endl;
      return MyGenerator{
        std::coroutine_handle<MyPromise>::from_promise(*this)
      };
    }
    
    MyAwaitable initial_suspend() {
      std::cout << "MyPromise::initial_suspend" << std::endl;
      return {};
    }

    MyAwaitable yield_value(int x) {
      std::cout << "MyPromise::yield_value, x = " << x << std::endl;
      val_ = x;
      return {};
    }

    MyAwaitable final_suspend() noexcept {
      std::cout << "MyPromise::final_suspend" << std::endl;
      return {};
    }
    
    void unhandled_exception() {
      std::cout << "MyPromise::unhandled_exception" << std::endl;
    }
    
    int get_very_custom_val() {
      std::cout << "MyPromise::get_very_custom_val (" << val_ << ")" << std::endl;
      return val_;
    }
    
  private:
    int val_;
  };
  
private:
  std::coroutine_handle<MyPromise> coro_;
};

MyGenerator allSquares() {
  std::cout << "allSquares called" << std::endl;
  for(int i = 1; ; ++i) {
    std::cout << "allSquares, will co_yield " << i * i << std::endl;
    co_yield (i * i);
    std::cout << "allSquares, co_yield of " << i << " done " << std::endl;
  }
}

int main ()
{
  std::cout << "main: will call allSquares" << std::endl;
  MyGenerator myCoroutineResult = allSquares();
  std::cout << "main: allSquares returned with generator" << std::endl << std::endl;
  for(int i = 0; myCoroutineResult.very_custom_next(); i++) {
    std::cout << "main: next iteration" << std::endl;
    std::cout << "main: calling myCoroutineResult.very_custom_value()" << std::endl;
    int r = myCoroutineResult.very_custom_value();
    std::cout << "main: myCoroutineResult.very_custom_value() = " << r << std::endl;
    std::cout << "main: end of current iteration" << std::endl << std::endl;
    if(i > 2) {
      std::cout << "main: did " << i + 1 << " iterations, breaking the loop" << std::endl;
      break;
    }
  }

  return 0;
}
