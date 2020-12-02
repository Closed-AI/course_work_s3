#include "MyLib.h"

using namespace std;

int main()
{
	OBJECT* obj = nullptr;
	start_setings(obj);
	
	while (obj->state != State::END)
	{
		print(obj);
		press_button(obj);
	}

	del(obj);

	check_memory_miss();

	return 0;
}