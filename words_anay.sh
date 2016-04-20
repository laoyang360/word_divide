#!/bin/bash
OUT_ALL_FILE=./divided_rst_all.txt
OUT_TOP20_FILE=./top20.txt

#清空处理
echo /dev/null > $OUT_TOP20_FILE
echo /dev/null > $OUT_TOP20_FILE


printf "WORDS\t COUNT\n" > $OUT_ALL_FILE

cat rst.txt | awk '{ list[$1]++ } \
END{
for(i in list)
{
	printf("%s\t %d\n", i, list[i]); 
}
}' | sort -nrk 2 | head -n 30  > $OUT_ALL_FILE


#wordlen=system("echo $i | wc -L")
#	if (($wordlen -gt  4))
#	then


cat $OUT_ALL_FILE | while read line
do
	#echo $line;
	left=`echo $line | awk '{print $1}'`
	leftlen=`echo $left | wc -L`
	if [ $leftlen -gt 2 ];then
		echo $line >> $OUT_TOP20_FILE
	fi
done

#最终输出结果
cat $OUT_TOP20_FILE | sort -nrk 2 | head -n 20  > $OUT_TOP20_FILE

