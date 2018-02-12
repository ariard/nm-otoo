#! /bin/zsh
diff <( nm $2 $1) <( ./ft_nm $2 $1)
