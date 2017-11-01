#!/usr/bin/env zsh
diff <(./ft_nm $@) <(nm $@)
if [ $? -eq 0 ]; then
	echo "OK    ✅    nm $@"
else
	echo "ERROR ✅    nm $@"
fi
