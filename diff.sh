#! /bin/zsh

if [ $1 = nm ]
then
	BIN=nm
	MYBIN=./ft_nm
elif [ $1 = ot ]
then
	BIN=otool
	OPT="-t"
	MYBIN=./ft_otool
else
	return
fi

diff <( $BIN $OPT $3 $2) <( $MYBIN $3 $2)
