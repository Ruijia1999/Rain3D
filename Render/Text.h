#ifndef RAIN_RENDER_TEXT
#define RAIN_RENDER_TEXT
#include "RenderData.h"
#include <string>
namespace Rain {
	namespace Render {
		class Text: public RenderData
		{
		public:
			std::string text;
			void Draw();
		};
	}
}




#endif // !RAIN_UI_TEXT

