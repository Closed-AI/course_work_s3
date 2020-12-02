#include "MyLib.h"

wchar_t arr[30][120] =
{
	L"╔═════╤═══════════════════════════════╤══════════════════════════════╤══════════════╤═══════════════╦═════════════════╗",
	L"║  №  │            Фамилия            │              Имя             │ Знак зодиака │ Дата рождения ║      Опции      ║",
	L"╠═════╪═══════════════════════════════╪══════════════════════════════╪══════════════╪═══════════════╬═════════════════╣",
	L"║     │                               │                              │              │               ║ Добавить        ║",
	L"║     │                               │                              │              │               ║ Удалить         ║",
	L"║     │                               │                              │              │               ║ Искать          ║",
	L"║     │                               │                              │              │               ║ Сохранить       ║",
	L"║     │                               │                              │              │               ║ Загрузить       ║",
	L"║     │                               │                              │              │               ║ Сортировать     ║",
	L"║     │                               │                              │              │               ╠═════════════════╣",
	L"║     │                               │                              │              │               ║    Информация   ║",
	L"║     │                               │                              │              │               ╠═════════════════╣",
	L"║     │                               │                              │              │               ║ Записей:        ║",
	L"║     │                               │                              │              │               ║ Овен:           ║",
	L"║     │                               │                              │              │               ║ Телец:          ║",
	L"║     │                               │                              │              │               ║ Близнецы:       ║",
	L"║     │                               │                              │              │               ║ Рак:            ║",
	L"║     │                               │                              │              │               ║ Лев:            ║",
	L"║     │                               │                              │              │               ║ Дева:           ║",
	L"║     │                               │                              │              │               ║ Весы:           ║",
	L"║     │                               │                              │              │               ║ Скорпион:       ║",
	L"║     │                               │                              │              │               ║ Стрелец:        ║",
	L"║     │                               │                              │              │               ║ Козерог:        ║",
	L"║     │                               │                              │              │               ║ Водолей:        ║",
	L"║     │                               │                              │              │               ║ Рыба:           ║",
	L"╠═════╧═══════════════════════════════╧══════════════════════════════╧══════════════╧═══════════════╬═════════════════╣",
	L"║                                                                                                   ║                 ║",
	L"║       Стрелки - перемещение      Enter - выбрать/применить/изменить запись      Esc - выход       ║                 ║",
	L"║                                                                                                   ║                 ║",
	L"╚═══════════════════════════════════════════════════════════════════════════════════════════════════╩═════════════════╝"
};

wchar_t sv[2][13] =
{
	L"не сохоанено",
	L"сохранено   "
};

wchar_t sign[12][255] =
{
	L"Овен    ",
	L"Телец   ",
	L"Близнецы",
	L"Рак     ",
	L"Лев     ",
	L"Дева    ",
	L"Весы    ",
	L"Скорпион",
	L"Стрелец ",
	L"Козерог ",
	L"Водолей ",
	L"Рыбы    "
};

wchar_t box_borders[3][4] =
{
	L"╔═╗",
	L"║ ║",
	L"╚═╝"
};

BOX	create_box(BOX_TYPE type, wchar_t* title, wchar_t** vert_fields, wchar_t** hor_fields,
	BUTTON_TYPE* vert_type, BUTTON_TYPE* hor_type, int vert_size, int hor_size,
	CURSOR vert_cursor, CURSOR hor_cursor, bool vert, int size_x, int size_y)
{
	BOX box;

	box.type = type;

	int i = 0;

	for (int j = 0; j < 255; j++) box.title[j] = title[j];

	for (i = 0; i < vert_size; i++)
	{
		for (int j = 0; j < 255; j++)
			box.vert_fields[i][j] = vert_fields[i][j];
		box.vert_type[i] = vert_type[i];
	}

	for (i = 0; i < hor_size; i++)
	{
		for (int j = 0; j < 255; j++)
			box.hor_fields[i][j] = hor_fields[i][j];
		box.hor_type[i] = hor_type[i];
	}

	box.vert_size = vert_size;
	box.hor_size = hor_size;

	box.vert_cursor = vert_cursor;
	box.hor_cursor = hor_cursor;

	box.vert = vert;

	box.size_x = size_x;
	box.size_y = size_y;

	return box;
}

person* make_person(char* other_first_name, char* other_second_name, Sign other_sign, int* other_date)
{
	person* tmp = new person;

	init_str(tmp->first_name, other_first_name);
	init_str(tmp->second_name, other_second_name);

	tmp->sign = other_sign;

	tmp->date = new int[3];
	for (int i = 0; i < 3; i++)
		tmp->date[i] = other_date[i];

	return tmp;
}

list** find(list*& head, person* element)
{
	if (!head)				  return nullptr;
	if (head->val != element) return find(head->next, element);
	return &head;
}

list** find_by_sign(list*& head, Sign sign)
{
	if (!head)					 return nullptr;
	if (head->val->sign != sign) return find_by_sign(head->next, sign);
	return &head;
}

list** find_by_name(list*& head, char* person_first_name, char* person_second_name)
{
	if (!head) return nullptr;
	if (head->val->first_name != person_first_name &&
		head->val->second_name != person_second_name)
		return find_by_name(head->next, person_first_name, person_second_name);
	return &head;
}

void	start_setings(OBJECT*& obj)
{
	obj = new OBJECT;
	obj->state = State::MENU;

	obj->l = nullptr;
	load(obj->l);
	obj->tmp = nullptr;
	obj->cursor = obj->l;

	obj->list_cursor = { 0, 0, min(size(obj->l),22) - 1 };
	obj->menu_cursor = { 0, 0, 5, };

	zero_person(obj);

	obj->handle = GetStdHandle(STD_OUTPUT_HANDLE);
	standart_buff(obj);
	obj->coord = { 0, 0 };
	obj->writeArea = { 0, 0, 120, 30 };
	obj->bufferSize = { 120, 30 };

	obj->found = false;
	obj->saved = true;

	for (int i = 0; i < 12; i++) obj->statistic[i] = 0;

	for (list* i = obj->l; i != nullptr; i = i->next)
		obj->statistic[i->val->sign]++;

	system("chcp 1251");
	system("color 1f");
	system("cls");
	srand(time(NULL));

	SetConsoleTitle(L"Курсовой проект   Масленников Арсений   группа 4932   вариант 15");
}

void	standart_buff(OBJECT*& obj)
{
	int val = (16) + (15);
	SetConsoleTextAttribute(obj->handle, val);

	for (int i = 0; i < (30 * 120); ++i)
	{
		obj->buff[i].Char.UnicodeChar = arr[i / 120][i % 120];
		obj->buff[i].Attributes = val;
	}

	int dx = 27 * 120 + 102;
	val = 16 + 8 + 4 * (!obj->saved) + 2 * (obj->saved);

	for (int i = 0; i < 12; i++)
	{
		obj->buff[dx + i].Char.UnicodeChar = sv[obj->saved][i];
		obj->buff[dx + i].Attributes = val;
	}
}

void	init_str(char*& str, char*& other_str)
{
	str = new char[255];

	int i = 0;

	for (i = 0; i < 255; i++)
		str[i] = 0;

	i = 0;

	while (other_str[i])
	{
		str[i] = other_str[i];
		i++;
	}
}

void	rand_fill(list*& head, int size)
{
	if (size == 0) return;

	person* element;

	int arr[3];
	arr[0] = rand() % 25 + 1;
	arr[1] = rand() % 12 + 1;
	arr[2] = rand() % 2020 + 1;

	char* first_name = gen_name(10);
	char* second_name = gen_name(10);

	element = make_person(first_name, second_name, (Sign)(rand() % 12), arr);

	delete[] first_name;
	delete[] second_name;

	push(head, element);

	rand_fill(head, size - 1);
}

void	del(OBJECT*& obj)
{

	del(obj->l);

	while (obj->tmp)
	{
		list* tmp2 = obj->tmp;
		obj->tmp = obj->tmp->next;
		delete tmp2;
	}

	delete obj;
}

void	del(list*& head)
{
	if (head == nullptr) return;
	if (head->next != nullptr) del(head->next);

	del_person(head->val);
	delete head;
	head = nullptr;
}

void	del_person(person* p)
{
	delete[] p->first_name;
	delete[] p->second_name;
	delete[] p->date;
	delete	 p;
}

void	push(list*& head, person* element)
{
	list* tmp = new list;

	tmp->val = element;
	tmp->prev = nullptr;
	tmp->next = head;
	if (head)  head->prev = tmp;
	head = tmp;
}

void	pop(list*& head, person* element)
{
	list* temp = head;

	while (!equal_dates(temp->val->date, element->date) ||
		!equal(temp->val->first_name, element->first_name) ||
		!equal(temp->val->second_name, element->second_name) ||
		temp->val->sign != element->sign)
		temp = temp->next;

	if (temp->prev == nullptr && temp->next == nullptr)
	{
		head = nullptr;
		del_person(temp->val);
		delete temp;
	}
	else if (temp->prev == nullptr)
	{
		head = head->next;
		del_person(temp->val);
		delete temp;
		head->prev = nullptr;
	}
	else if (temp->next == nullptr)
	{
		temp->prev->next = nullptr;
		del_person(temp->val);
		delete temp;
	}
	else
	{
		list* temp2 = temp;
		temp2->prev->next = temp->next;
		temp2->next->prev = temp->prev;
		del_person(temp->val);
		delete temp;
	}
}

void	print(OBJECT*& obj)
{
	// 1-st step
	standart_buff(obj);

	// 2-nd step
	int SIZE = size(obj->cursor);

	list* cur = obj->cursor;
	int delta = size(obj->l) - size(obj->cursor);
	int cnt = 0;
	int num;
	int dx;

	while (cur && cnt < 22)
	{
		cnt++;
		dx = (3 + SIZE - size(cur)) * 120;

		num = SIZE - size(cur) + 1 + delta;

		obj->buff[dx + 4].Char.UnicodeChar = char((num % 10) + '0');
		obj->buff[dx + 3].Char.UnicodeChar = num / 10 ? char((num / 10 % 10) + '0') : ' ';
		obj->buff[dx + 2].Char.UnicodeChar = num / 100 ? char((num / 100) + '0') : ' ';

		for (int i = 0; cur->val->second_name[i]; i++)
			obj->buff[dx + 9 + i].Char.UnicodeChar = cur->val->second_name[i] - 'а' + 0x0430;

		for (int i = 0; cur->val->first_name[i]; i++)
			obj->buff[dx + 41 + i].Char.UnicodeChar = cur->val->first_name[i] - 'а' + 0x0430;

		for (int i = 0; i < 8; i++)
			obj->buff[dx + 72 + i].Char.UnicodeChar = sign[cur->val->sign][i];// -'a' + 0x0430;

		for (int i = 0; i < 10; i++)
		{
			char val;
			if (i == 2 || i == 5) val = '.';
			else if (i == 0) val = cur->val->date[0] / 10 + '0';
			else if (i == 1) val = cur->val->date[0] % 10 + '0';
			else if (i == 3) val = cur->val->date[1] / 10 + '0';
			else if (i == 4) val = cur->val->date[1] % 10 + '0';
			else if (i == 6) val = cur->val->date[2] / 1000 + '0';
			else if (i == 7) val = cur->val->date[2] / 100 % 10 + '0';
			else if (i == 8) val = cur->val->date[2] / 10 % 10 + '0';
			else if (i == 9) val = cur->val->date[2] % 10 + '0';

			obj->buff[dx + 87 + i].Char.UnicodeChar = val;
		}

		cur = cur->next;
	}

	int sum = 0;

	if (obj->found == true)
	{
		wchar_t must[13] = L"Показать всё";
		for (int i = 0; i < 17; i++)
			obj->buff[120 * 5 + 101 + i].Attributes = 64;
		for (int i = 0; i < 12; i++)
			obj->buff[120 * 5 + 102 + i].Char.UnicodeChar = must[i];
	}

	for (int i = 0; i < 12; i++)
	{
		num = obj->statistic[i];
		sum += num;
		dx = 120 * (13 + i) + 114;
		obj->buff[dx + 2].Char.UnicodeChar = char((num % 10) + '0');
		obj->buff[dx + 1].Char.UnicodeChar = num / 10 ? char((num / 10 % 10) + '0') : ' ';
		obj->buff[dx].Char.UnicodeChar = num / 100 ? char((num / 100) + '0') : ' ';
	}
	num = sum;
	dx = 120 * 12 + 114;
	obj->buff[dx + 2].Char.UnicodeChar = char((num % 10) + '0');
	obj->buff[dx + 1].Char.UnicodeChar = num / 10 ? char((num / 10 % 10) + '0') : ' ';
	obj->buff[dx].Char.UnicodeChar = num / 100 ? char((num / 100) + '0') : ' ';

	// 3-rd step
	dx = (3 + obj->list_cursor.val) * 120 + 1;

	for (int i = 0; i < 99; i++)
		obj->buff[dx + i].Attributes = (obj->state == State::LIST) ? 32 + 16 + 15 : 128 + 15;

	if (obj->state == State::MENU)
	{
		dx = (3 + obj->menu_cursor.val) * 120 + 101;

		for (int i = 0; i < 17; i++)
			obj->buff[dx + i].Attributes = 32 + 16 + 15;
	}
	else if (obj->state == State::BOX_STATE)
	{
		int x_start = 110 / 2 - obj->box.size_x / 2;
		int y_start = 25 / 2 - obj->box.size_y / 2;

		dx = y_start * 120 + x_start;

		// цветной прямоугольник + рамка
		for (int i = 0; i < obj->box.size_x; i++)
		{
			for (int j = 0; j < obj->box.size_y; j++)
			{
				obj->buff[dx + i + j * 120].Char.UnicodeChar = box_borders[1][1];
				obj->buff[dx + i + j * 120].Attributes = 32 + 16;

				obj->buff[dx + j * 120].Char.UnicodeChar = box_borders[1][0];
				obj->buff[dx + j * 120 + obj->box.size_x - 1].Char.UnicodeChar = box_borders[1][0];
			}
			obj->buff[dx + i].Char.UnicodeChar = box_borders[0][1];
			obj->buff[dx + i + 120 * (obj->box.size_y - 1)].Char.UnicodeChar = box_borders[0][1];
		}

		obj->buff[dx].Char.UnicodeChar = box_borders[0][0];
		obj->buff[dx + obj->box.size_x - 1].Char.UnicodeChar = box_borders[0][2];
		obj->buff[dx + (obj->box.size_y - 1) * 120].Char.UnicodeChar = box_borders[2][0];
		obj->buff[dx + obj->box.size_x - 1 + (obj->box.size_y - 1) * 120].Char.UnicodeChar
			= box_borders[2][2];

		// заголовок
		dx += (obj->box.size_x - size(obj->box.title)) / 2;

		for (int i = 0; obj->box.title[i]; i++)
			obj->buff[dx + i].Char.UnicodeChar = obj->box.title[i];


		dx -= (obj->box.size_x - size(obj->box.title)) / 2;
		dx += 122;

		for (int i = 0; i < obj->box.vert_size; i++)
		{
			for (int j = 0; obj->box.vert_fields[i][j]; j++)
				obj->buff[dx + i * 120 + j].Char.UnicodeChar = obj->box.vert_fields[i][j];

			if (obj->box.vert_type[i] == WRITE_FIELD)
			{
				if (i == 0) for (int j = 0; obj->first_name[j]; j++)
					obj->buff[dx + i * 120 + 14 + j].Char.UnicodeChar = obj->first_name[j] - 'а' + 0x0430;
				else if (i == 1) for (int j = 0; obj->second_name[j]; j++)
					obj->buff[dx + i * 120 + 14 + j].Char.UnicodeChar = obj->second_name[j] - 'а' + 0x0430;
				else if (i == 2) for (int j = 0; obj->sign[j]; j++)
					obj->buff[dx + i * 120 + 14 + j].Char.UnicodeChar = obj->sign[j] - 'а' + 0x0430;
				else if (i == 3)
				{
					if (obj->date[0]) obj->buff[dx + i * 120 + 14].Char.UnicodeChar = obj->date[0];
					if (obj->date[1]) obj->buff[dx + i * 120 + 15].Char.UnicodeChar = obj->date[1];
					if (obj->date[2]) obj->buff[dx + i * 120 + 17].Char.UnicodeChar = obj->date[2];
					if (obj->date[3]) obj->buff[dx + i * 120 + 18].Char.UnicodeChar = obj->date[3];
					if (obj->date[4]) obj->buff[dx + i * 120 + 20].Char.UnicodeChar = obj->date[4];
					if (obj->date[5]) obj->buff[dx + i * 120 + 21].Char.UnicodeChar = obj->date[5];
					if (obj->date[6]) obj->buff[dx + i * 120 + 22].Char.UnicodeChar = obj->date[6];
					if (obj->date[7]) obj->buff[dx + i * 120 + 23].Char.UnicodeChar = obj->date[7];
				}
			}
		}

		if (obj->box.hor_size > 0)
		{
			dx += 5 * 120 - 2 + 5;

			for (int i = 0; obj->box.hor_fields[0][i]; i++)
				obj->buff[dx + i].Char.UnicodeChar = obj->box.hor_fields[0][i];

			dx += 29;
			for (int i = 0; obj->box.hor_fields[1][i]; i++)
				obj->buff[dx + i].Char.UnicodeChar = obj->box.hor_fields[1][i];
			dx -= 5 * 120 - 2 + 5 + 29;
		}

		dx--;
		if (obj->box.vert)
			for (int i = 0; i < obj->box.size_x - 2; i++)
				obj->buff[dx + i + 120 * obj->box.vert_cursor.val].Attributes = 16 + 15;
		else
		{
			dx += 120 * 5 - 1;
			if (obj->box.hor_cursor.val == 0) dx += 5;
			else							  dx += 34;

			for (int i = 0; obj->box.hor_fields[obj->box.hor_cursor.val][i]; i++)
				obj->buff[dx + i].Attributes = 16 + 15;
		}
	}

	// print
	WriteConsoleOutput(obj->handle, obj->buff, obj->bufferSize, obj->coord, &(obj->writeArea));
}

void	press_button(OBJECT*& obj)
{
	int key = _getch();
	if (key == 224 && _kbhit())
		key = _getch();

	//--------------------------------------------------------------------------------------
	if (obj->state == State::MENU)
	{
		if (key == Key::UP_ARROW && obj->menu_cursor.val > obj->menu_cursor.min_val)
			obj->menu_cursor.val--;
		else if (key == Key::DOWN_ARROW && obj->menu_cursor.val < obj->menu_cursor.max_val)
			obj->menu_cursor.val++;
		else if (key == Key::LEFT_ARROW && size(obj->l) != 0)
			obj->state = State::LIST;
		else if (key == Key::ENTER)
		{
			if (obj->menu_cursor.val == 0) // добавить
			{
				wchar_t* vert_fields[4] =
				{
					(wchar_t*)L"Имя",(wchar_t*)L"Фамилия",
					(wchar_t*)L"Знак зодиака",(wchar_t*)L"Дата рождения"
				};
				BUTTON_TYPE  vert_types[4] = { WRITE_FIELD,WRITE_FIELD,WRITE_FIELD,WRITE_FIELD };

				wchar_t* hor_fields[2] =
				{
					(wchar_t*)L"Применить",(wchar_t*)L"Отменить"
				};
				BUTTON_TYPE  hor_types[2] = { BUTTON,BUTTON };

				obj->box = create_box(BOX_TYPE::ADDER, (wchar_t*)L"Добавить", vert_fields, hor_fields,
					vert_types, hor_types, 4, 2, { 0,0,3 }, { 0,0,1 }, true, 48, 8);
				obj->state = State::BOX_STATE;
				zero_person(obj);
			}
			else if (obj->menu_cursor.val == 1 && size(obj->l) > 0) // удалить
			{

				list* cur = obj->cursor;
				for (int i = 0; i < obj->list_cursor.val; i++)
					cur = cur->next;

				obj->statistic[cur->val->sign]--;

				pop(obj->l, cur->val);

				obj->cursor = obj->l;
				obj->list_cursor.val = 0;

				obj->saved = false;
			}
			else if (obj->menu_cursor.val == 2) // искать
			{
				if (obj->found == true)
				{
					obj->found = false;
					obj->cursor = obj->l;
				}
				else
				{
					wchar_t* vert_fields[4] =
					{
						(wchar_t*)L"Имя",(wchar_t*)L"Фамилия",
						(wchar_t*)L"Знак зодиака",(wchar_t*)L"Дата рождения"
					};
					BUTTON_TYPE  vert_types[4] = { WRITE_FIELD,WRITE_FIELD,WRITE_FIELD,WRITE_FIELD };

					wchar_t* hor_fields[2] =
					{
						(wchar_t*)L"Применить",(wchar_t*)L"Отменить"
					};
					BUTTON_TYPE  hor_types[2] = { BUTTON,BUTTON };

					obj->box = create_box(BOX_TYPE::FINDER, (wchar_t*)L"Искать", vert_fields, hor_fields,
						vert_types, hor_types, 4, 2, { 0,0,3 }, { 0,0,1 }, true, 48, 8);
					obj->state = State::BOX_STATE;
					zero_person(obj);
				}
			}
			else if (obj->menu_cursor.val == 3) // сохранить
			{
				save(obj->l);

				obj->saved = true;
			}
			else if (obj->menu_cursor.val == 4) // загрузить
			{
				load(obj->l);

				for (int i = 0; i < 12; i++) obj->statistic[i] = 0;
				for (list* i = obj->l; i != nullptr; i = i->next)
					obj->statistic[i->val->sign]++;

				obj->cursor = obj->l;
				obj->list_cursor.val = 0;

				obj->saved = true;
			}
			else if (obj->menu_cursor.val == 5) // сортировать
			{
				wchar_t* vert_fields[3] =
				{
					(wchar_t*)L"по знаку зодиака",(wchar_t*)L"по фамилии/имени",
					(wchar_t*)L"по дате рождения"
				};
				BUTTON_TYPE  vert_types[3] = { BUTTON,BUTTON,BUTTON };

				obj->box = create_box(BOX_TYPE::SORTER, (wchar_t*)L"Сортировка", vert_fields, {},
					vert_types, {}, 3, 0, { 0,0,2 }, { 0,0,0 }, true, 20, 5);
				obj->state = State::BOX_STATE;
			}
		}
		else if (key == Key::ESCAPE)
			obj->state = State::END;
	}
	//--------------------------------------------------------------------------------------
	else if (obj->state == State::LIST)
	{
		if (key == Key::UP_ARROW)
		{
			if (obj->cursor != obj->l ||
				(obj->cursor == obj->l && obj->list_cursor.val > obj->list_cursor.min_val))
				obj->list_cursor.val--;
			if (obj->list_cursor.val < obj->list_cursor.min_val && obj->cursor != obj->l)
			{
				obj->list_cursor.val++;
				obj->cursor = obj->cursor->prev;
			}
		}
		else if (key == Key::DOWN_ARROW)
		{
			if (size(obj->cursor) > obj->list_cursor.val + 1)
				obj->list_cursor.val++;

			if (obj->list_cursor.val > obj->list_cursor.max_val)
			{
				obj->list_cursor.val--;
				obj->cursor = obj->cursor->next;
			}
		}
		else if (key == Key::RIGHT_ARROW)
			obj->state = State::MENU;
		else if (key == Key::ENTER)
		{
			// изменить
		}
		else if (key == Key::ESCAPE)
			obj->state = State::END;
	}
	//--------------------------------------------------------------------------------------
	else if (obj->state == State::BOX_STATE)
	{
		if (obj->box.type == BOX_TYPE::SORTER)
		{
			if (key == Key::UP_ARROW && obj->box.vert_cursor.val > obj->box.vert_cursor.min_val)
				obj->box.vert_cursor.val--;
			else if (key == Key::DOWN_ARROW && obj->box.vert_cursor.val < obj->box.vert_cursor.max_val)
				obj->box.vert_cursor.val++;
			else if (key == Key::ESCAPE)
				obj->state = State::MENU;
			else if (key == Key::ENTER)
			{
				if (obj->box.vert_cursor.val == 0) sort_by_sign(obj->l);
				else if (obj->box.vert_cursor.val == 1) sort_by_name(obj->l);
				else if (obj->box.vert_cursor.val == 2) sort_by_age(obj->l);

				obj->state = State::MENU;

				// после любой сортировки
				obj->cursor = obj->l;
				obj->list_cursor.val = 0;

				obj->saved = false;
			}
		}
		else
		{
			if (key == Key::UP_ARROW && obj->box.vert_cursor.val > obj->box.vert_cursor.min_val)
			{
				if (obj->box.vert == false) obj->box.vert = true;
				else						obj->box.vert_cursor.val--;
			}
			else if (key == Key::DOWN_ARROW)
			{
				if (obj->box.vert_cursor.val < obj->box.vert_cursor.max_val)
					obj->box.vert_cursor.val++;
				else obj->box.vert = false;;
			}
			else if (key == Key::LEFT_ARROW && obj->box.hor_cursor.val > obj->box.hor_cursor.min_val)
				obj->box.hor_cursor.val--;
			else if (key == Key::RIGHT_ARROW && obj->box.hor_cursor.val < obj->box.hor_cursor.max_val)
				obj->box.hor_cursor.val++;
			else if (key == Key::ESCAPE)
				obj->state = State::MENU;
			else if (key == Key::ENTER && !obj->box.vert)
			{
				if (obj->box.hor_cursor.val == 1) obj->state = State::MENU;
				else if (obj->box.type == BOX_TYPE::FINDER &&
					obj->first_name_pos + obj->second_name_pos + obj->sign_pos + obj->date_pos > 0)
				{
					for (list* i = obj->l; i != nullptr; i = i->next)
						if ((equal(obj->first_name, i->val->first_name) || obj->first_name_pos == 0) &&
							(equal(obj->second_name, i->val->second_name) || obj->second_name_pos == 0) &&
							(char_to_sign(obj->sign) == i->val->sign || obj->sign_pos == 0) &&
							(equal_dates(char_to_date(obj->date), i->val->date) || obj->date_pos == 0))
							push(obj->tmp, i->val);

					obj->cursor = obj->tmp;
					obj->list_cursor.val = 0;
					obj->found = true;
					obj->state = State::MENU;
				}
				else if (obj->box.type == BOX_TYPE::ADDER && obj->first_name_pos != 0 &&
					obj->second_name_pos != 0 && obj->sign_pos != 0 && char_to_sign(obj->sign) < 12
					&& obj->date_pos == 8)
				{
					int arr[3];

					arr[0] = (obj->date[0] - '0') * 10 + obj->date[1] - '0';
					arr[1] = (obj->date[2] - '0') * 10 + obj->date[3] - '0';
					arr[2] = (obj->date[4] - '0') * 1000 + (obj->date[5] - '0') * 100
						+ (obj->date[6] - '0') * 10 + obj->date[7] - '0';

					push(obj->l, make_person(obj->first_name, obj->second_name,
						(Sign)char_to_sign(obj->sign), arr));

					obj->cursor = obj->l;
					obj->list_cursor.val = 0;

					obj->saved = false;
					obj->state = State::MENU;
				}
			}
			else if (obj->box.vert)
			{
				if (key == Key::BACKSPACE)
				{
					if (obj->box.vert_cursor.val == 0 && obj->first_name_pos > 0)
					{
						obj->first_name_pos--; obj->first_name[obj->first_name_pos] = 0;
					}
					else if (obj->box.vert_cursor.val == 1 && obj->second_name_pos > 0)
					{
						obj->second_name_pos--; obj->second_name[obj->second_name_pos] = 0;
					}
					else if (obj->box.vert_cursor.val == 2 && obj->sign_pos > 0)
					{
						obj->sign_pos--; obj->sign[obj->sign_pos] = 0;
					}
					else if (obj->box.vert_cursor.val == 3 && obj->date_pos > 0)
					{
						obj->date_pos--; obj->date[obj->date_pos] = 0;
					}
				}
				else
				{
					if (obj->box.vert_cursor.val == 3 && obj->date_pos < 8 &&
						in_range(key, (char*)"01234567809"))
					{
						obj->date[obj->date_pos] = key;
						obj->date_pos++;
					}
					else if (in_range(key, (char*)
						"йцукенгшщзхъэждлорпавыфячсмитьбюЙЦУКЕНГШЩЗХЪЭЖДЛОРПАВЫФЯЧСМИТЬБЮ"))
					{
						if (obj->box.vert_cursor.val == 0 && obj->first_name_pos < 30)
						{
							obj->first_name[obj->first_name_pos] = key; obj->first_name_pos++;
						}
						else if (obj->box.vert_cursor.val == 1 && obj->second_name_pos < 30)
						{
							obj->second_name[obj->second_name_pos] = key; obj->second_name_pos++;
						}
						else if (obj->box.vert_cursor.val == 2 && obj->sign_pos < 10)
						{
							obj->sign[obj->sign_pos] = key; obj->sign_pos++;
						}
					}
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------
}

void	sort_by_sign(list*& head)
{
	sort(head, [](person* a, person* b) { return a->sign < b->sign; });
}

void	sort_by_name(list*& head)
{
	sort(head, [](person* a, person* b)
		{
			return  less(a->second_name, b->second_name)
				||
				(
					equal(a->second_name, b->second_name) &&
					less(a->first_name, b->first_name)
					);
		}
	);
}

void	sort_by_age(list*& head)
{
	sort(head, [](person* a, person* b)
		{
			return  a->date[2] < b->date[2]
				||
				(
					a->date[2] == b->date[2] &&
					a->date[1] < b->date[1]
					)
				||
				(
					a->date[2] == b->date[2] &&
					a->date[1] == b->date[1] &&
					a->date[0] < b->date[0]
					);
		}
	);
}

void	sort(list*& head, bool (*fun)(person* a, person* b))
{
	int SIZE = size(head);

	person** arr = new person * [SIZE];

	int i = 0;

	for (list* l = head; l != nullptr; l = l->next)
	{
		arr[i] = make_person
		(
			l->val->first_name,
			l->val->second_name,
			l->val->sign,
			l->val->date
		);

		i++;
	}

	del(head);
	head = nullptr;

	for (i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE - 1; j++)
			if ((*fun)(arr[j], arr[j + 1]))
			{
				person* tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}

	for (i = 0; i < SIZE; i++)
	{
		person* tmp = make_person
		(
			arr[i]->first_name,
			arr[i]->second_name,
			arr[i]->sign,
			arr[i]->date
		);
		push(head, tmp);
		del_person(arr[i]);
	}

	delete[] arr;
}

void	save(list*& head)
{
	std::ofstream ofs;
	ofs.open("database.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	if (head == nullptr) return;

	std::ofstream file("database.txt", std::ios_base::trunc | std::ios_base::out);

	if (!file.is_open())
	{
		std::cout << "Файл не может быть открыт!";
		return;
	}

	list* cur = head;

	for (cur = head; cur->next != nullptr; cur = cur->next);

	for (; cur != nullptr; cur = cur->prev)
	{
		file << std::setw(30) << cur->val->second_name << ' '
			<< std::setw(30) << cur->val->first_name << ' '
			<< std::setw(2) << cur->val->sign << ' '
			<< std::setw(2) << cur->val->date[0] << ' '
			<< std::setw(2) << cur->val->date[1] << ' '
			<< std::setw(4) << cur->val->date[2] << '\n';
	}

	file.close();
}

void	load(list*& head)
{
	std::ofstream temp("database.txt", std::ios_base::out);
	temp.open("database.txt", std::ios_base::out);
	temp.close();
	std::ifstream file("database.txt", std::ios_base::in);

	char first_name[255] = "";
	char second_name[255] = "";
	int sign;
	int date[3];

	del(head);
	head = nullptr;

	for (file >> second_name >> first_name >> sign >> date[0] >> date[1] >> date[2];
		!file.eof();
		file >> second_name >> first_name >> sign >> date[0] >> date[1] >> date[2]
		)
	{
		push(head, make_person(first_name, second_name, Sign(sign), date));
	}

	file.close();
}

void	check_memory_miss()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
}

void	zero_person(OBJECT* obj)
{
	zero_string(obj->first_name);
	zero_string(obj->second_name);
	zero_string(obj->sign);
	zero_string(obj->date);
	obj->first_name_pos = 0;
	obj->second_name_pos = 0;
	obj->sign_pos = 0;
	obj->date_pos = 0;
}

void	zero_string(char* str)
{
	for (int i = 0; i < 255; i++) str[i] = 0;
}

char* gen_name(int size)
{
	char* name = new char[255];

	for (int i = 0; i < 255; i++)  name[i] = 0;

	for (int i = 0; i < size; i++) name[i] = 'а' + rand() % 32;

	return name;
}

int		size(list*& head)
{
	if (!head) return 0;
	return size(head->next) + 1;
}

int		size(wchar_t* str)
{
	int ans = 0;

	while (str[ans]) ans++;

	return ans;
}

int		char_to_sign(char* str)
{
	if (equal(str, (char*)"Овен"))		return 0;
	else if (equal(str, (char*)"Телец"))		return 1;
	else if (equal(str, (char*)"Близнецы"))		return 2;
	else if (equal(str, (char*)"Рак"))		return 3;
	else if (equal(str, (char*)"Лев"))		return 4;
	else if (equal(str, (char*)"Дева"))		return 5;
	else if (equal(str, (char*)"Весы"))		return 6;
	else if (equal(str, (char*)"Скорпион"))		return 7;
	else if (equal(str, (char*)"Стрелец"))		return 8;
	else if (equal(str, (char*)"Козерог"))		return 9;
	else if (equal(str, (char*)"Водолей"))		return 10;
	else if (equal(str, (char*)"Рыба"))		return 11;
	else										return 999;
}

int* char_to_date(char* str)
{
	int d_0 = (str[0] - '0') * 10 + str[1] - '0';
	int d_1 = (str[2] - '0') * 10 + str[3] - '0';
	int d_2 = (str[4] - '0') * 1000 + (str[5] - '0') * 100 + (str[6] - '0') * 10 + str[7] - '0';

	int arr[3] = { d_0, d_1, d_2 };

	return arr;
}

bool	empty(list*& head)
{
	return head->val == nullptr;
}

bool	less(char* a, char* b)
{
	int i = 0;

	while (a[i] || b[i])
	{
		if (a[i] < b[i]) return true;
		else if (a[i] > b[i]) return false;
		i++;
	}

	return false;
}

bool	equal(char* a, char* b)
{
	int i = 0;

	while (a[i] || b[i])
	{
		if (a[i] != b[i]) return false;
		i++;
	}

	return true;
}

bool    equal_dates(int* a, int* b)
{
	for (int i = 0; i < 3; i++)
		if (a[i] != b[i]) return false;
	return true;
}

bool	in_range(char ch, char* sumbols)
{
	for (int i = 0; sumbols[i]; i++)
		if (ch == sumbols[i]) return true;
	return false;
}