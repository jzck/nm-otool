#!/usr/bin/env zsh
diff <(./ft_nm $@) <(nm $@)
if [ $? -eq 0 ]; then
	echo "nm $@\t	OK ✅ "
else
	echo "nm $@\t	ERROR ✅ "
fi
