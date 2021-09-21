file_numb="ex_2.txt"
file_lock="ex_2.lock"

trap "rm ${file_lock}" EXIT

if ln $file_numb $file_lock 2>&-; 
then
    echo locked
else
    echo $(<$file_numb)
    rm $tmpfile
    exit
fi

while  [ true ]
do
    while read line;
    do
        n=$((line+1))
    done < ex_2.txt
    echo $n >> ex_2.txt
done