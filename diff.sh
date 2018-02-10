#! /bin/zsh
diff <( nm $1) <( ./ft_nm $1)
