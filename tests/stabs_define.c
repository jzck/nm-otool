#define NONE	42
#define TWO(a, b)	(a + (a) + 2 * b)
#define ONE(c)	(c + 19)

main(int argc, char *argv[])
{
	func(NONE, TWO(10, 11));
	func(NONE, ONE(23));

#undef ONE
#define ONE(c)	(c + 23)

	func(NONE, ONE(-23));

	return (0);
}

int global;

func(int arg1, int arg2)
{
	global = arg1 + arg2;
}
