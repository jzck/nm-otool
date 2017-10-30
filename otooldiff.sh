#!/usr/bin/env zsh
make
diff <(./ft_otool $@) <(otool -t $@)
if [ $? -eq 0 ]; then
	echo "OK ✅"
else
	echo "ERROR ❎"
fi
