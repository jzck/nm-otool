#!/usr/bin/env zsh
diff <(./ft_otool $@) <(otool $@)
if [ $? -eq 0 ]; then
	echo "otool $@\t	OK ✅ "
else
	echo "otool $@\t	ERROR ✅ "
fi
