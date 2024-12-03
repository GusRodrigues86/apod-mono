#ifndef api_Runner_hpp
#define api_Runner_hpp

#include "oatpp/web/server/api/ApiController.hpp"

#include <list>
#include <thread>

namespace APOD::API {
    class Runner {
        public:
        explicit Runner();

        void run(std::list<std::thread>& threads);
    };
}
#endif // api_Runner_hpp