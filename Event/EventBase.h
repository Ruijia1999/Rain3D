#ifndef RAIN_EVENT_EVENTBASE
#define RAIN_EVENT_EVENTBASE

#include <vector>
#include <functional>

namespace Rain {
	namespace Event {
		struct NullType {};
		template<class inParam = NullType>
		class EventBase
		{
			
		private:
			typedef void Handler(inParam);
			std::vector<std::function<Handler>> m_handlers;
		public:
			template<class Func>
			int Bind(Func func) {
				m_handlers.push_back(func);
				return 0;
			}
			void Remove(int indices) {

			}
			void Operate(inParam param) {
				for (auto func : m_handlers) {
					func(param);
				}
			}
		};

	}
}
#endif //RAIN_EVENT_EVENTBAS

