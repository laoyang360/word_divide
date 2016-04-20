# word_divide
1.word_divide for files used friso(open source).

词频统计实现
引言： 在不了解分词技术之前，甚至以为只有英文才可以分词，中文没有。后来接触发现，原来已经有很多基于统计的成熟的中文分词技术。在这些开源分词的”肩“上，想实现分词统计也就变得非常容易。
以下借助《2016年两会政府报告》为源文件，统计李克强总理的讲话词频。


1、输入：给定一篇不固定长度的.txt文本文件，文件内容不限于：短信记录、报告。
输出：1）、词、频率；2）、形成词云。（借助工具实现即可）

2、需要技术：
1）分词技术
本文选用：Friso分词开源技术。Friso是使用C语言开发的一款高性能中文分词器，使用流行的mmseg算法实现。
（以下两行摘自Friso官网）Friso是使用C语言开发的一款高性能中文分词器，使用流行的mmseg算法实现。
完全基于模块化设计和实现，可以很方便的植入到其他程序中，例如：MySQL，PHP等。同时支持对UTF-8/GBK编码的切分。

2）Shell脚本排序、统计

3、流程梳理
Step1:使用Friso开源代码实现读文件分词，源报告文件存入dict_test.txt中，并将结果输出到rst.txt结果文件。（源代码src中，没有该实现，需要自己实现）
Step2:Shell脚本统计分词结果，并将结果以"词 词频"的形式输出到统计文件divided_rst_all.txt。
Step3:对词进行人工干预特殊处理（如“单个字符 等、要 意义不大 可以去掉，不统计”），形成top20.txt最终结果文件。

4、源码
1）分词实现
原有接口只提供了输入buffer逐行进行分词。现需要新增如下两个接口：
/*
**@param:[out]文件buffer，输出。
**@param:lpszFilename:文件名
**@brief:读取文件，写入buffer
**@return:1,成功；其他代表失败。
**
*/
int ReadFile(char **FileStr,const char* lpszFilename)

/*
**@param:pszRst:待写入文件；
**@param:nRstLen:待写入长度。
**@brief:分词结果写入文件
**@return:空
**
*/
void writeFile(const char* pszRst, int nRstLen)

2）脚本实现
详见代码
#最终输出结果
cat $OUT_TOP20_FILE | sort -nrk 2 | head -n 20 > $OUT_TOP20_FILE

5、统计结果
[root@WEB-W0XX wordDivide_src]# cat top20.txt 
发展 113
建设 63
推进 60
经济 57
改革 57
创新 54
政策 45
加快 41
加强 41
政府 40
实施 39
促进 37
社会 36
制度 35
企业 35
全面 34
提高 33
推动 33
我们 30
增长 28

6、小结
1）可以用作各种类型的文件的词频统计，如：短信、邮件信息等。
2）若想精确的分词，需要用最新的词库。
3）可以借助“词云”友好界面展示结果。


附：
1、Friso下载地址：
http://git.oschina.net/lionsoul/friso/attach_files
2、常见分词技术分类：
http://witmax.cn/4-open-source-cws.html
3、全面分词技术介绍：
http://www.scholat.com/vpost.html?pid=22647

作者：铭毅天下
http://blog.csdn.net/laoyang360/


