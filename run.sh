
[ -f pid ] && PID=`cat pid`
[ -p cmd ] && rm cmd
#mkfifo cmd
#[ AnsiCGE.cpp -nt a.out ] && echo "compiling" && g++ --std=c++14 AnsiCGE.cpp
#echo "execute"

#dist/Debug/GNU-Linux/shellcge < cmd &
#cgepid=$!

cgein="/proc/$PID/fd/0"
exec 3>$cgein

echo greet > $cgein
echo exit > $cgein
echo greet > $cgein

echo end.
