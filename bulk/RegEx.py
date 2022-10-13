'''
Author: avert-win
Date: 2022-07-09 22:39:00
LastEditTime: 2022-07-10 00:10:42
FilePath: \ProgramDaily\RegEx.py
Description: 简介
LastEditors: avert-win
'''
# regular expression with example: 
# https://towardsdatascience.com/regular-expressions-clearly-explained-with-examples-822d76b037b4
'''
Basic regex characters
  Characters
    escape: \ 
    any: .
    digit: \d           not a digit: \D
    word character: \w  not a word character: \W
    whitespace: \s      not a whitespace: \S
    word boundary: \b
    begining of string: ^
    end of string: $
  Groupings
    matches characters in brackets: []
    matches characters not in brackets: [^ ]
    either or: |
    capturing group: ()
  Quantifiers: these must follow a character, otherwise re raises an error.
    any: *
    1 or more: +
    0 or 1: ?
    exact number: {}
    range of number: [min, max]

re.OF(operation flag): 
    re.I: case-insensitive
    re.L: interprets words according to the current locale. #? what?
    re.M: $ and ^ for both line and string(the default is only string).

'''
import re

sentence = 'cat_and_dogs 2022-07-09 \n A-2024-07-09'

match = re.match(r'A.*-(\d{2})*-(\d{2})*', sentence, re.M)
search = re.search(r'A.*-(\d{2})*-(\d{2})*', sentence, re.M)
'''
A: constant character;
.*: any number of any characters;
-: constant character;
(\d{2}): group, consists of digits, the number of digits is 2;

heap like this.
'''

# match: match from begining.
if match:
    print('match!')
    print(match.group())
    print(match.groups())
else:
    print('no match.')

print()

# search and match at any position.
if search:
    print('found!')
    print(search.group())
    print(search.groups())
else:
    print('cannot found!')