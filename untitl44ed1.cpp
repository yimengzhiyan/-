#!/bin/bash #调用bash解释器

#初始化各种变量
#其中yuan为原始字母表，plug为从右往左看的原始表，roto1-roto5为5个转子，result为我们的输出结果，RB,RC为两个反射板
yuan=(A B C D E F G H I J K L M N O P Q R S T U V W X Y Z)
plug=(A B C D E F G H I J K L M N O P Q R S T U V W X Y Z)
roto1=(E K M F L G D Q V Z N T O W Y H X U S P A I B R C J)
roto2=(A J D K S I R U X B L H W T M C Q G Z N P Y F V O E)
roto3=(B D F H J L C P R T X V Z N Y E I W G A K M U S Q O)
roto4=(E S O V P Z J A Y Q U I R H X L N F T G K D C M W B)
roto5=(V Z B R G I T Y U P S D N H L X A W M J Q O F E C K)
result=0
RB=(Y R U H Q S L D P X N G O K M I E B F Z C W V J A T)
RC=(F V P J I A O Y E D R Z X W G C T K U Q S B N M H L)

# 选择反射板（两个选择B和C）
read -p "请输入选择的反射板(B/C，注意输入格式，例如使用反射板B，就输入B即可):" fan

# 选择转子（5选3），输入转子1，即对应初始化变量过程中的R1
read -p "请输入转子序号(注意输入格式，必须连续输入，中间不得出现空格，如选择123转子就输入123)：" rotor

# 对输入的转子进行截取，例如r1就是截取出来的第一个转子
r1=${rotor:0:1};r2=${rotor:1:1};r3=${rotor:2:1}

# 定义字母环初始刻度
read -p "请输入三个转子的字母环刻度(注意输入格式，此处需要以一个空格作为分隔符，例如：01 23 15):" ringsettings
# 同理，也对输入的字母环刻度进行截取，例如rin1就是截取出来的第一组字母环刻度
rin1=${ringsettings:0:2};rin2=${ringsettings:3:2};rin3=${ringsettings:6:3}

# 定义转子起始位置
read -p "请输入三个转子的起始位置，也就是每日密钥的三个字母(注SS意输入格式，必须连续输入，不得有空格，例如：JWK) "  begin
# 同理，对三个转子的起始位置进行截取，例如beg1就是截取出来的第一个初始字母
beg1=${begin:0:1};beg2=${begin:1:1};beg3=${begin:2:1}

# 定义初始函数（函数的名字的意思就是初始），初始函数的作用是将每个转子对应的yuan变量初始到相应转子的初始位置
chushi()
{ n=0
	while eval [ $p != ${yuan[$n]} ];do let n++;done #通过循环找到需要加密字母对应转子的位置
	for (( n_1=0; n_1<$n; n_1++))
		do
			eval  n_2=\${roto$q[0]}; #找到当前所用转子的第一个字母
	for (( n_3=0; n_3<25; n_3++ ))
		do
			eval  roto$q[$n_3]=\${roto$q[$n_3+1]} ; #将转子的每一个字母顺次往后移动一位
	done
	eval  roto$q[25]=$n_2 ; #首位变末位
	done
}

# 对三个转子的字母盘都进行初始化（都使用初始函数）
p=$beg1;q=$r1;chushi
p=$beg2;q=$r2;chushi
p=$beg3;q=$r3;chushi
# 输入插线板（就是输入需要交换的字母表）
read -p "请输入插线板中的10对交换字母(注意输入格式，每对字母间需要用空格隔开，例如:YT IS PQ KV EZ WU BJ FG OA MH):" jh
j1=0;j2=1;j4=1;j5=0
while [ $j1 -le 27 ]
	do
		j3=0
		while eval [ ${jh:$j1:1} != ${plug[$j3]} ];do let j3++;done
j6=0
while eval [ ${jh:$j4:1} != ${plug[$j6]} ];do let j6++;done
plug[$j3]=${jh:$j2:1}; plug[$j6]=${jh:$j5:1}
let j1=j1+3; let j2=j2+3; let j4=j4+3; let j5=j5+3
done
echo ${plug[*]}

# 读取明文（就是我们需要加密的原文）
read -p "请输入加密内容：" string

z=0
while [ $z != ${#string} ]
	do
# 通过插线板首次加密
		num=${string:$z:1};j0=0
while [ $num != ${plug[$j0]} ];do let j0++;done
index1=0;index2=0;index3=0;index4=0;index5=0;index6=0;index7=0;index8=0
#第一个转子正向加密
while     [ ${plug[$j0]} != ${yuan[$index1]} ];do let index1++;done
# 第二个转子正向加密
while eval [ \${roto$r1[$index1]} != ${yuan[$index2]} ];do let index2++;done
# 第三个转子正向加密
while eval [ \${roto$r2[$index2]} != ${yuan[$index3]} ];do let index3++;done
# 反射板加密
while eval [ \${roto$r3[$index3]} != ${yuan[$index4]} ];do let index4++;done
# 第三个转子反向加密
while eval [ \${roto$r3[$index5]} != \${roto$fan[$index4]} ];do let index5++;done
# 第二个转子反向加密
while eval [ \${roto$r2[$index6]} != ${yuan[$index5]} ];do let index6++;done
# 第一个转子反向加密
while eval [ \${roto$r1[$index7]} != ${yuan[$index6]} ];do let index7++;done
# 第二次插板加密
while      [ ${plug[$index8]} != ${yuan[$index7]} ];do let index8++;done
eval  result[$z+1]=${plug[$index8]}

# 所有转子旋转过程实现
xz()
{  eval  i=\${roto$q[0]}
	for (( j=0; j<25; j++ ))
		do eval  roto$q[$j]=\${roto$q[$j+1]};done
	eval  roto$q[25]="$i"
}
q="$r";xz
# 第二转子进位
jinwei()
{  eval r1=\${roto$q[0]}
	for (( u=0; u<25; u++ ))
		do
			eval  roto$q[$u]=\${roto$q[$u+1]}
	done
	eval  roto$q[25]="$r1"
}
if eval [ \${roto$r[0]} == \${yuan[ $rin1 - 1 ]} ]
	then q="$s";jinwei
fi
# 第三转子进位
if eval  [ \${roto$s[0]} == \${yuan[ $rin2 - 1 ]} ]
	then q="$r";jinwei
q="$s";jinwei
fi
let z++
done
unset result[0]

# 输出翻译得到的结果
echo ${result[*]}|tr -d " "
