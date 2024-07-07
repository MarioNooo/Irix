/* This file is for Shift JIS charset, and created by tommy@valley.ne.jp.
 */
#include <global.h>
#include "m_string.h"

uchar NEAR ctype_sjis[257] =
{
    0,				/* For standard library */
    0040, 0040, 0040, 0040, 0040, 0040, 0040, 0040,	/* NUL ^A - ^G */
    0040, 0050, 0050, 0050, 0050, 0050, 0040, 0040,	/* ^H - ^O */
    0040, 0040, 0040, 0040, 0040, 0040, 0040, 0040,	/* ^P - ^W */
    0040, 0040, 0040, 0040, 0040, 0040, 0040, 0040,	/* ^X - ^Z ^[ ^\ ^] ^^ ^_ */
    0110, 0020, 0020, 0020, 0020, 0020, 0020, 0020,	/* SPC ! " # $ % ^ ' */
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,	/* ( ) * + , - . / */
    0204, 0204, 0204, 0204, 0204, 0204, 0204, 0204,	/* 0 1 2 3 4 5 6 7 */
    0204, 0204, 0020, 0020, 0020, 0020, 0020, 0020,	/* 8 9 : ; < = > ? */
    0020, 0201, 0201, 0201, 0201, 0201, 0201, 0001,	/* @ A B C D E F G */
    0001, 0001, 0001, 0001, 0001, 0001, 0001, 0001,	/* H I J K L M N O */
    0001, 0001, 0001, 0001, 0001, 0001, 0001, 0001,	/* P Q R S T U V W */
    0001, 0001, 0001, 0020, 0020, 0020, 0020, 0020,	/* X Y Z [ \ ] ^ _ */
    0020, 0202, 0202, 0202, 0202, 0202, 0202, 0002,	/* ` a b c d e f g */
    0002, 0002, 0002, 0002, 0002, 0002, 0002, 0002,	/* h i j k l m n o */
    0002, 0002, 0002, 0002, 0002, 0002, 0002, 0002,	/* p q r s t u v w */
    0002, 0002, 0002, 0020, 0020, 0020, 0020, 0040,	/* x y z { | } + DEL */
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0020, 0020, 0020,
    0020, 0020, 0020, 0020, 0020, 0000, 0000, 0000,
};

uchar NEAR to_lower_sjis[]=
{
  '\000','\001','\002','\003','\004','\005','\006','\007',
  '\010','\011','\012','\013','\014','\015','\016','\017',
  '\020','\021','\022','\023','\024','\025','\026','\027',
  '\030','\031','\032','\033','\034','\035','\036','\037',
  ' ',	 '!',	'"',   '#',   '$',   '%',   '&',   '\'',
  '(',	 ')',	'*',   '+',   ',',   '-',   '.',   '/',
  '0',	 '1',	'2',   '3',   '4',   '5',   '6',   '7',
  '8',	 '9',	':',   ';',   '<',   '=',   '>',   '?',
  '@',	 'a',	'b',   'c',   'd',   'e',   'f',   'g',
  'h',	 'i',	'j',   'k',   'l',   'm',   'n',   'o',
  'p',	 'q',	'r',   's',   't',   'u',   'v',   'w',
  'x',	 'y',	'z',   '[',   '\\',  ']',   '^',   '_',
  '`',	 'a',	'b',   'c',   'd',   'e',   'f',   'g',
  'h',	 'i',	'j',   'k',   'l',   'm',   'n',   'o',
  'p',	 'q',	'r',   's',   't',   'u',   'v',   'w',
  'x',	 'y',	'z',   '{',   '|',   '}',   '~',   '\177',
  '\200','\201','\202','\203','\204','\205','\206','\207',
  '\210','\211','\212','\213','\214','\215','\216','\217',
  '\220','\221','\222','\223','\224','\225','\226','\227',
  '\230','\231','\232','\233','\234','\235','\236','\237',
  '\240','\241','\242','\243','\244','\245','\246','\247',
  '\250','\251','\252','\253','\254','\255','\256','\257',
  '\260','\261','\262','\263','\264','\265','\266','\267',
  '\270','\271','\272','\273','\274','\275','\276','\277',
  '\300','\301','\302','\303','\304','\305','\306','\307',
  '\310','\311','\312','\313','\314','\315','\316','\317',
  '\320','\321','\322','\323','\324','\325','\326','\327',
  '\330','\331','\332','\333','\334','\335','\336','\337',
  '\340','\341','\342','\343','\344','\345','\346','\347',
  '\350','\351','\352','\353','\354','\355','\356','\357',
  '\360','\361','\362','\363','\364','\365','\366','\367',
  '\370','\371','\372','\373','\374','\375','\376','\377',
};

uchar NEAR to_upper_sjis[]=
{
  '\000','\001','\002','\003','\004','\005','\006','\007',
  '\010','\011','\012','\013','\014','\015','\016','\017',
  '\020','\021','\022','\023','\024','\025','\026','\027',
  '\030','\031','\032','\033','\034','\035','\036','\037',
  ' ',	 '!',	'"',   '#',   '$',   '%',   '&',   '\'',
  '(',	 ')',	'*',   '+',   ',',   '-',   '.',   '/',
  '0',	 '1',	'2',   '3',   '4',   '5',   '6',   '7',
  '8',	 '9',	':',   ';',   '<',   '=',   '>',   '?',
  '@',	 'A',	'B',   'C',   'D',   'E',   'F',   'G',
  'H',	 'I',	'J',   'K',   'L',   'M',   'N',   'O',
  'P',	 'Q',	'R',   'S',   'T',   'U',   'V',   'W',
  'X',	 'Y',	'Z',   '[',   '\\',  ']',   '^',   '_',
  '`',	 'A',	'B',   'C',   'D',   'E',   'F',   'G',
  'H',	 'I',	'J',   'K',   'L',   'M',   'N',   'O',
  'P',	 'Q',	'R',   'S',   'T',   'U',   'V',   'W',
  'X',	 'Y',	'Z',   '{',   '|',   '}',   '~',   '\177',
  '\200','\201','\202','\203','\204','\205','\206','\207',
  '\210','\211','\212','\213','\214','\215','\216','\217',
  '\220','\221','\222','\223','\224','\225','\226','\227',
  '\230','\231','\232','\233','\234','\235','\236','\237',
  '\240','\241','\242','\243','\244','\245','\246','\247',
  '\250','\251','\252','\253','\254','\255','\256','\257',
  '\260','\261','\262','\263','\264','\265','\266','\267',
  '\270','\271','\272','\273','\274','\275','\276','\277',
  '\300','\301','\302','\303','\304','\305','\306','\307',
  '\310','\311','\312','\313','\314','\315','\316','\317',
  '\320','\321','\322','\323','\324','\325','\326','\327',
  '\330','\331','\332','\333','\334','\335','\336','\337',
  '\340','\341','\342','\343','\344','\345','\346','\347',
  '\350','\351','\352','\353','\354','\355','\356','\357',
  '\360','\361','\362','\363','\364','\365','\366','\367',
  '\370','\371','\372','\373','\374','\375','\376','\377',
};

uchar NEAR sort_order_sjis[]=
{
  '\000','\001','\002','\003','\004','\005','\006','\007',
  '\010','\011','\012','\013','\014','\015','\016','\017',
  '\020','\021','\022','\023','\024','\025','\026','\027',
  '\030','\031','\032','\033','\034','\035','\036','\037',
  ' ',	 '!',	'"',   '#',   '$',   '%',   '&',   '\'',
  '(',	 ')',	'*',   '+',   ',',   '-',   '.',   '/',
  '0',	 '1',	'2',   '3',   '4',   '5',   '6',   '7',
  '8',	 '9',	':',   ';',   '<',   '=',   '>',   '?',
  '@',	 'A',	'B',   'C',   'D',   'E',   'F',   'G',
  'H',	 'I',	'J',   'K',   'L',   'M',   'N',   'O',
  'P',	 'Q',	'R',   'S',   'T',   'U',   'V',   'W',
  'X',	 'Y',	'Z',   '[',   '\\',  ']',   '^',   '_',
  '`',	 'A',	'B',   'C',   'D',   'E',   'F',   'G',
  'H',	 'I',	'J',   'K',   'L',   'M',   'N',   'O',
  'P',	 'Q',	'R',   'S',   'T',   'U',   'V',   'W',
  'X',	 'Y',	'Z',   '{',   '|',   '}',   '~',   '\177',
  '\200','\201','\202','\203','\204','\205','\206','\207',
  '\210','\211','\212','\213','\214','\215','\216','\217',
  '\220','\221','\222','\223','\224','\225','\226','\227',
  '\230','\231','\232','\233','\234','\235','\236','\237',
  '\240','\241','\242','\243','\244','\245','\246','\247',
  '\250','\251','\252','\253','\254','\255','\256','\257',
  '\260','\261','\262','\263','\264','\265','\266','\267',
  '\270','\271','\272','\273','\274','\275','\276','\277',
  '\300','\301','\302','\303','\304','\305','\306','\307',
  '\310','\311','\312','\313','\314','\315','\316','\317',
  '\320','\321','\322','\323','\324','\325','\326','\327',
  '\330','\331','\332','\333','\334','\335','\336','\337',
  '\340','\341','\342','\343','\344','\345','\346','\347',
  '\350','\351','\352','\353','\354','\355','\356','\357',
  '\360','\361','\362','\363','\364','\365','\366','\367',
  '\370','\371','\372','\373','\374','\375','\376','\377',
};
