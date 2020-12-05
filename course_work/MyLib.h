#pragma once

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

enum State
{
	LIST,
	MENU,
	BOX_STATE,
	END
};

enum Key
{
	BACKSPACE   = 8,
	ENTER       = 13,
	ESCAPE      = 27,
	UP_ARROW    = 72,
	LEFT_ARROW  = 75,
	RIGHT_ARROW = 77,
	DOWN_ARROW  = 80
};

enum Sign 
{
	Aries = 0,
	Taurus,
	Twins,
	Crayfish,
	Lion,
	Virgo,
	Libra,
	Scorpio,
	Sagittarius,
	Capricorn,
	Aquarius,
	Fish
};

struct CURSOR
{
	int val;
	int min_val;
	int max_val;
};

struct person
{
	char* first_name;
	char* second_name;
	Sign  sign;
	int*  date;
};

struct list
{
	person* val;
	list*	next;
	list*	prev;
};

struct NOTE
{
	wchar_t text[255];
	int		color;
};

enum BUTTON_TYPE
{
	BUTTON,
	WRITE_FIELD
};

enum BOX_TYPE
{
	SORTER,
	FINDER,
	ADDER,
	CHANGER
};

struct BOX
{
	BOX_TYPE    type;

	wchar_t		title[255];
	wchar_t		vert_fields[10][255];
	wchar_t		hor_fields [10][255];

	BUTTON_TYPE	vert_type[10];
	BUTTON_TYPE	hor_type [10];

	int			vert_size;
	int			hor_size;

	CURSOR		vert_cursor;
	CURSOR		hor_cursor;

	bool		vert;

	int			size_x;
	int			size_y;
};

struct OBJECT
{
	State		state;

	list*		l;
	list*		tmp;
	list*		cursor;
	list*		changer;

	CURSOR		list_cursor;
	CURSOR		menu_cursor;

	BOX		box;
	NOTE	note;

	//--для поиска/добавления--
	char first_name[255];
	char second_name[255];
	char sign[255];
	char date[255];
	
	int first_name_pos;
	int second_name_pos;
	int sign_pos;
	int date_pos;
	//-------------------------

	HANDLE		handle;
	CHAR_INFO	buff[30*120];
	COORD		coord;
	SMALL_RECT	writeArea;
	COORD		bufferSize;

	bool		found;
	bool		saved;
	int			statistic[12];
};

BOX		create_box			(BOX_TYPE type, wchar_t* title, wchar_t** vert_fields, wchar_t** hor_fields,
							 BUTTON_TYPE* vert_type, BUTTON_TYPE* hor_type, int vert_size, int hor_size,
							 CURSOR vert_cursor, CURSOR hor_cursor, bool vert, int size_x, int size_y);

person* make_person			(char* other_first_name, char* other_second_name, Sign  other_sign, int* other_date);

list**	find				(list*& head, person* element);
list**	find_by_sign		(list*& head, Sign sign);
list**	find_by_name		(list*& head, char* person_first_name, char* person_second_name);

void	start_setings		(OBJECT*& obj);
void	standart_buff		(OBJECT*& obj);
void	init_str			(char*& str, char*& other_str);
void	rand_fill			(list*& head,int size);
void	del					(OBJECT*& obj);
void	del					(list*& head);
void	del_person			(person* p);
void	push				(list*& head, person* element);
void	pop					(list*& head, person* element);
void	print				(OBJECT*& obj);
void	press_button		(OBJECT*& obj);
void	sort_by_sign		(list*& head);
void	sort_by_name		(list*& head);
void	sort_by_age			(list*& head);
void	sort				(list*& head, bool (*fun)(person* a, person* b));
void	save				(list*& head);
void	load				(list*& head);
void	check_memory_miss	();
void	zero_person			(OBJECT* obj);
void	zero_string			(char* str);

char*	gen_name			(int size);
char*	gen_sign			(int sign);

int		size				(list*& head);
int		size				(wchar_t* str);
int		size				(char* str);
int		char_to_sign		(char* str);
int*    char_to_date		(char* str);

bool	empty				(list*& head);
bool	less				(char* a, char* b);
bool	equal				(char* a, char* b);
bool    equal_dates			(int*  a, int*  b);
bool	in_range			(char ch, char* sumbols);
bool	is_russion			(char ch);
bool	correct_date		(int* date);