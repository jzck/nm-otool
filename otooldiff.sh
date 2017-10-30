#!/usr/bin/env zsh
diff <(./ft_otool $@) <(otool $@)
if [ $? -eq 0 ]; then
	echo "OK ✅"
else
	echo "ERROR ❎"
fi
