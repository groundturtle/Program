'''
Author: avert-win
Date: 2022-05-07 15:43:33
LastEditTime: 2022-05-07 21:22:57
FilePath: \ProgramDaily\TagValidator.py
Description: 判断标签是否有效（正确），要求有一个标签包裹全部，标签内除`<![CDATA[...]]>`中的省略号可以是任意内容以外，保证不包含'<'。
LastEditors: avert-win
'''
#* Using list.pop() and list.append() as stack in python.
#* `'<'.isupper()` is `false`, but `'A<'.isupper()` give you `True`.

'''
本题判断条件众多，简化问题的关键有两点，
    1. 找到尖括号(对)后，将其中内容当作一个整体一次处理完，不要再反复进入其中；如此，可以免去大部分需要和状态记录相关联的条件判断（如不同部分对每个字符有不同要求）
    2. 处理好边界情况和特殊情况，如标签全部匹配、但没有一个标签能包裹全部；或字符串的开头/结尾有单独在标签以外的字符。

在认清以上两点之后，就可以排除边界情况，然后只针对每个尖括号对的内容进行单独解析。

1. 判断开头是否是标签开头，如果不是，必错；
2. 每一次，如果已经有过了标签开头，但现在标签数为0且字符串解析未结束，说明没有一个标签包裹全部，错误；
3. 判断结尾是否是标签结束、标签是否匹配、解析完成后是否有剩余标签。
    第一点，如果结尾不是标签结束，要么有剩余标签、要么在上一个标签（最后一个标签）解析结束后继续解析剩余字符串时，剩余标签数就已经为0而判断错误，因此不必处理；
    第二点，和中间的其它标签一样判断即可，不必区分是否末尾；
    第三点，判断最后列表是否为空。
4. 对于中间字符串，
    第一，如果是开头标签则入栈，如果是结尾标签则判断是否匹配最后一个开头标签；
    第二，如果是CDATA，则直接找到末尾，不需要关心中间部分。

https://leetcode-cn.com/problems/tag-validator/submissions/
'''

class Solution:
    def isValid(self, code: str) -> bool:

        if code[0] != '<':
            return False

        tagNames = []
        length = len(code)
        atLeastOne = False

        i = 0
        while(i<length):

            # Already got a tag but not has no tag.
            if atLeastOne and len(tagNames)==0:
                return False

            if code[i] == '<':

                # '<' is the last one.
                if i == length-1:
                    return False

                # followed by start tag.
                elif code[i+1].isupper():
                    j = code.find('>', i)               # when calculating length, j is not included('>').
                    if j != -1 and j-i-1 <= 9 and code[i+1:j].upper() == code[i+1:j]:
                        for c in code[i+1:j]:
                            if not c.isupper():
                                return False
                        tagNames.append(code[i+1:j])
                        atLeastOne = True
                        i = j
                    else:
                        return False

                # followed by ending tag.
                elif code[i+1] == '/':
                    if len(tagNames)==0:
                        return False
                    j = code.find('>', i)
                    if j != -1 and code[i+2:j] == tagNames.pop():
                        i = j                   # i then will increase one.
                    else:
                        return False

                # followed by CDATA.
                elif code[i+1] == '!':
                    if not atLeastOne:
                        return False
                    if code[i+2:i+9] == '[CDATA[':
                        inCdata = True
                        j = code.find(']]>', i)
                        if j != -1:
                            i = j+2
                        else:
                            return False
                    else:
                        return False

                # else situation: except tag and CDATA.
                else:
                    return False
                
            i += 1

        # If there is at least one valid tag and no tag remained.
        if len(tagNames) == 0 and atLeastOne:
            return True
        else:
            return False   

# code = "<DIV><YFSYYS><UVBNIQ><XPMXUNT><WNGMV><OJJGQREMT><Z><GEJDP><LIQS><NCVYU><RAS><UYFKCJCDN><NA><POJVYT><Z><TDC><VUIZQC><BNANGX><TOF><MR>MK</MR></TOF></BNANGX></VUIZQC></TDC></Z></POJVYT></NA></UYFKCJCDN></RAS></NCVYU></LIQS></GEJDP></Z></OJJGQREMT></WNGMV></XPMXUNT></UVBNIQ></YFSYYS></DIV>"
code = "<![CDATA[ABC]]><TAG>sometext</TAG>"
# code = "<A<></A<>"
solu = Solution()
print(solu.isValid(code))