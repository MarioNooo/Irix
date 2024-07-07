<!-- 	Cray Research, A Silicon Graphics Company
	Software Publications
	DocBook DTD stylesheet
	February 24, 1998 (Production Version 2.4)
	drd@cray.com
-->


<sheet >



<?INSTED COMMENT: GROUP admonition>

<group name="admonition">
	<break-before>	Line	</>
	<text-before><blockquote></>
	<text-after><join(/)blockquote></>
</group>


<style name="CAUTION" group="admonition">
	<text-before><blockquote><img src="/icons/caution.gif" alt="[caution]" align=left><b>Caution: <join(/)b></>
</style>

<style name="IMPORTANT" group="admonition">
	<text-before><blockquote><b>Important: <join(/)b></>
</style>

<style name="NOTE" group="admonition">
	<select>if(attr(role),NOTE.attr(role),NOTE.DEFAULT)</>
</style>

<style name="NOTE.DEFAULT" group="admonition">
	<text-before><blockquote><b>Note: <join(/)b></>
</style>

<style name="NOTE.ANSI-ISO" group="admonition">
	<text-before><blockquote><b>ANSI/ISO: <join(/)b></>
</style>

<style name="NOTE.OPENMP" group="admonition">
	<text-before><blockquote><b>OpenMP: <join(/)b></>
</style>

<style name="TIP" group="admonition">
	<text-before><blockquote><b>Tip: <join(/)b></>
</style>

<style name="WARNING" group="admonition">
	<text-before><blockquote><b>Warning: <join(/)b></>
</style>



<?INSTED COMMENT: GROUP code>

<group name="code">
	<foreground>	coral	</>
	<text-before><code></>
	<text-after>join('<','/code>')</>
</group>

<style name="CLASSNAME" group="code">
</style>

<style name="FUNCTION" group="code">
</style>

<style name="KEYCODE" group="code">
</style>

<style name="OPTION" group="code">
</style>

<style name="OPTIONAL" group="code">
	<text-before>[</>
	<text-after>] </>
</style>

<style name="PARAMETER" group="code">
</style>

<style name="PROPERTY" group="code">
</style>

<style name="STRUCTFIELD" group="code">
</style>

<style name="STRUCTNAME" group="code">
</style>

<style name="SYSTEMITEM" group="code">
</style>

<style name="TOKEN" group="code">
</style>

<style name="TYPE" group="code">
</style>



<?INSTED COMMENT: GROUP dd>

<group name="dd">
	<left-indent>	+=25	</>
	<break-before>	Line	</>
	<text-before><dd><p></>
	<text-after><join(/)p><join(/)dd></>
</group>

<style name="DEFLISTENTRY,LISTITEM" group="dd">
</style>

<style name="GLOSSDEF" group="dd">
	<left-indent>	150	</>
	<width>	200	</>
	<break-after>	Line	</>
</style>

<style name="HEAD2" group="dd">
</style>

<style name="REVHISTORY,REVISION,DATE" group="dd">
</style>

<style name="REVHISTORY,REVISION,REVREMARK" group="dd">
</style>



<?INSTED COMMENT: GROUP displayhead>

<group name="displayhead">
	<break-before>	Line	</>
	<text-before><p align=center></>
	<text-after><join(/)p></>
</group>

<style name="ABSTRACT,TITLE" group="displayhead">
</style>

<style name="DEFLIST,TITLE" group="displayhead">
	<text-before><p align=center></>
</style>

<style name="EQUATION,TITLE" group="displayhead">
</style>

<style name="EXAMPLE,TITLE" group="displayhead">
	<text-before><p align=center>Example gcnum(ancestor(example)). </>
</style>

<style name="IMPORTANT,TITLE" group="displayhead">
</style>



<?INSTED COMMENT: GROUP dl>

<group name="dl">
	<foreground>	RoyalBlue4	</>
	<space-before>	14	</>
	<break-before>	Line	</>
	<text-before>if(ancestor(para),<br><br>,)<dl></>
	<text-after><join(/)dl></>
</group>

<style name="DEFLIST" group="dl">
</style>

<style name="GLOSSENTRY" group="dl">
</style>

<style name="REVHISTORY" group="dl">
	<text-before> <h2>Record of Revision <join(/)h2><dl></>
</style>



<?INSTED COMMENT: GROUP dt>

<group name="dt">
	<break-before>	Line	</>
	<text-before><dt><p></>
	<text-after><join(/)p><join(/)dt></>
</group>

<style name="GLOSSENTRY,GLOSSTERM" group="dt">
	<text-before><dt><p><em></>
	<text-after><join(/)em><join(/)p><join(/)dt></>
</style>

<style name="HEAD1" group="dt">
</style>

<style name="REVHISTORY,REVISION,REVNUMBER" group="dt">
</style>

<style name="TERM" group="dt">
</style>



<?INSTED COMMENT: GROUP em>

<group name="em">
	<font-slant>	Italics	</>
	<text-before><em></>
	<text-after><join(/)em></>
</group>

<style name="ABBREV" group="em">
</style>

<style name="ACRONYM" group="em">
</style>

<style name="FIRSTTERM" group="em">
</style>

<style name="GLOSSTERM" group="em">
</style>

<style name="MARKUP" group="em">
</style>

<style name="TRADEMARK" group="em">
</style>


<?INSTED COMMENT: GROUP figure>

<group name="figure">
	<break-before>	Line	</>
</group>

<style name="FIGURE" group="figure">
        <text-before><blockquote></>
        <text-after><join(/)blockquote></>
</style>

<style name="FIGURE,TITLE" group="figure">
	<text-before><P><B>Figure gcnum(ancestor(figure)).<join(/)B> </>
        <text-after><join(/)P><P></>
</style>

<style name="SCREENSHOT" group="figure">
        <text-before><blockquote></>
        <text-after><join(/)blockquote></>
</style>

<style name="SCREENSHOT,TITLE" group="figure">
	<text-before><P><B></>
        <text-after><join(/)B><join(/)P><P></>
</style>

<style name="GRAPHIC" group="figure">
	<space-before>	12	</>
	<icon-position>	Right	</>
	<break-before>	Line	</>
	<inline>	raster filename="attr(entityref)"	</>
</style>


<?INSTED COMMENT: GROUP h1>

<group name="h1">
	<font-family>	lucida	</>
	<font-weight>	Bold	</>
	<font-size>	24	</>
	<foreground>	blue3	</>
	<line-spacing>	24	</>
	<break-before>	Line	</>
	<text-before><h1></>
	<text-after><join(/)h1></>
</group>

<style name="APPENDIX,TITLE" group="h1">
	<text-before><h1>Appendix format(gcnum(ancestor(appendix)),LETTER). </>
</style>

<style name="BOOK,TITLE" group="h1">
</style>

<style name="CHAPTER,TITLE" group="h1">
	<text-before><h1>Chapter gcnum(ancestor(chapter)). </>
</style>

<style name="GLOSSARY,TITLE" group="h1">
</style>

<style name="NEWFEATURES,TITLE" group="h1">
</style>

<style name="PART,TITLE" group="h1">
	<text-before><h1>Part gcnum(ancestor(part)). </>
</style>

<style name="PREFACE,TITLE" group="h1">
	<text-before><h1></>
</style>



<?INSTED COMMENT: GROUP h2>

<group name="h2">
	<font-family>	lucida	</>
	<font-weight>	Bold	</>
	<font-size>	16	</>
	<foreground>	blue3	</>
	<line-spacing>	16	</>
	<break-before>	Line	</>
	<text-before><h2></>
	<text-after><join(/)h2></>
</group>

<style name="APPENDIX,SECTION,TITLE" group="h2">
	<text-before><h2>format(gcnum(ancestor(appendix)),LETTER).cnum(ancestor(section)) </>
</style>

<style name="CHAPTER,SECTION,TITLE" group="h2">
	<text-before><h2>gcnum(ancestor(chapter)).cnum(ancestor(section)) </>
</style>

<style name="PREFACE,SECTION,TITLE" group="h2">
</style>



<?INSTED COMMENT: GROUP h3>

<group name="h3">
	<font-family>	lucida	</>
	<font-weight>	Bold	</>
	<foreground>	blue3	</>
	<break-before>	Line	</>
	<text-before><h3></>
	<text-after><join(/)h3></>
</group>

<style name="APPENDIX,SECTION,SECTION,TITLE" group="h3">
	<text-before><h3>format(gcnum(ancestor(appendix)),LETTER).cnum(ancestor(me(),section,2)).cnum(ancestor(section)) </>
</style>

<style name="CHAPTER,SECTION,SECTION,TITLE" group="h3">
	<text-before><h3>gcnum(ancestor(chapter)).cnum(ancestor(me(),section,2)).cnum(ancestor(section)) </>
</style>



<?INSTED COMMENT: GROUP h4>

<group name="h4">
	<font-family>	lucida	</>
	<font-weight>	Bold	</>
	<font-slant>	Italics	</>
	<foreground>	blue3	</>
	<break-before>	Line	</>
	<text-before><h4></>
	<text-after><join(/)h4></>
</group>

<style name="APPENDIX,SECTION,SECTION,SECTION,TITLE" group="h4">
	<text-before><h4>format(gcnum(ancestor(appendix)),LETTER).cnum(ancestor(me(),section,3)).cnum(ancestor(me(),section,2)).cnum(ancestor(section)) </>
</style>

<style name="CHAPTER,SECTION,SECTION,SECTION,TITLE" group="h4">
	<text-before><h4>gcnum(ancestor(chapter)).cnum(ancestor(me(),section, 3)).cnum(ancestor(me(),section,2)).cnum(ancestor(section)) </>
</style>



<?INSTED COMMENT: GROUP h5>

<group name="h5">
	<font-family>	lucida	</>
	<font-weight>	Medium	</>
	<font-slant>	Italics	</>
	<foreground>	blue3	</>
	<break-before>	Line	</>
	<text-before><h4></>
	<text-after><join(/)h4></>
</group>

<style name="APPENDIX,SECTION,SECTION,SECTION,SECTION,TITLE" group="h5">
	<text-before><h4>format(gcnum(ancestor(appendix)),LETTER).cnum(ancestor(me(),section,4)).cnum(ancestor(me(),section,3)).cnum(ancestor(me(),section,2)).cnum(ancestor(section)) </>
</style>

<style name="CHAPTER,SECTION,SECTION,SECTION,SECTION,TITLE" group="h5">
	<text-before><h4>gcnum(ancestor(chapter)).cnum(ancestor(me(),section,4)).cnum(ancestor(me(),section,3)).cnum(ancestor(me(),section,2)).cnum(ancestor(section)) </>
</style>



<?INSTED COMMENT: GROUP li>

<!-- 	We want lists to have "open" spacing: every list item, every 
	paragraph within a list item and every list should be separated
	by exactly one blank line. Each element in the list will need
        to set blank spacing around it.
  -->


<group name="li">
	<left-indent>	+=15	</>
	<first-indent>	-15	</>
	<space-before>	14	</>
	<break-before>	Line	</>
	<text-before><li></>
	<text-after><join(/)li></>
</group>

<style name="ITEM" group="li">
</style>

<style name="LISTITEM" group="li">
</style>


<?INSTED COMMENT: GROUP mono>

<!-- This group includes all elements that change the font to a monospace 
     font. The HTML tag depends on function and desired appearance. The 
     default is <code>. The group monodisplay includes elements that set
     off monospace text from the body.
  -->
<group name="mono">
	<font-family>	fixed	</>
	<text-before><code></>
	<text-after><join(/)code></>
</group>

<!-- Note: Default ?? value is for unrecognized sectionref attribute values. -->
<style name="COMMAND" group="mono">
	<text-after><join(/)code>if(attr(sectionref),if(eq(attr(sectionref),blank),,\(gamut(attr(sectionref), '1 1B 1B-U 1M 1M-U 1X 1X-U 2 3 3C 3C-U 3F 3F-U 3G 3G-U 3I 3I-U 3K 3K-U 3L 3L-U 3M 3M-U 3N 3N-U 3O 3O-U 3R 3R-U 3S 3S-U 3X 3X-U 4 4P 4P-U 5 5X 5X-U 6 7 7D 7D-U 7X 7X-U 8 8E 8E-U','1 1B 1B 1M 1M 1X 1X 2 3 3C 3C 3F 3F 3G 3G 3I 3I 3K 3K 3L 3L 3M 3M 3N 3N 3O 3O 3R 3R 3S 3S 3X 3X 4 4P 4P 5 5X 5X 6 7 7D 7D 7X 7X 8 8E 8E', join('??'))\)),)</>
</style>

<style name="FILENAME" group="mono">
</style>

<style name="HARDWARE" group="mono">
	<foreground>	SandyBrown	</>
	<text-before><kbd></>
	<text-after><join(/)kbd></>
</style>

<style name="INTERFACEDEFINITION" group="mono">
	<text-before><BR> <BR><DL><DT></>
	<text-after><join(/)DT><join(/)DL></>
</style>

<style name="INTERFACEDEFINITION,INTERFACE" group="mono">
        <text-before><DL><DT><code></>
	<text-after><join(/)DT><join(/)DL><join(/)code></>
</style>

<style name="INTERFACE,INTERFACE" group="mono">
        <text-before>if(contains(qtag(me()),INTERFACEDEFINITION),<DL><DT><code>\ -> ,\ -> )</>
        <text-after>if(contains(qtag(me()),INTERFACEDEFINITION),<join(/)code><join(/)DT><join(/)DL>,<join(/)code>)</>
</style>

<style name="INTERFACE" group="mono">
	<text-before><code></>
	<text-after><join(/)code></>
</style>

<style name="KEYCAP" group="mono">
</style>

<style name="LITERAL" group="mono">
</style>

<style name="USERINPUT" group="mono">
	<text-before><kbd><b></>
	<text-after><join(/)b><join(/)kbd></>
</style>



<?INSTED COMMENT: GROUP monodisplay>

<!-- See the comment for the group mono. -->
<group name="monodisplay">
	<font-family>	fixed	</>
	<foreground>	DarkOrange3	</>
	<break-before>	Line	</>
	<text-before><pre></>
	<text-after><join(/)pre></>
</group>

<style name="LITERALLAYOUT" group="monodisplay">
</style>

<style name="PROGRAMLISTING" group="monodisplay">
</style>

<style name="SCREEN" group="monodisplay">
	<text-before>if(ancestor(para),<p>,,)<table border cellpadding="10" cellspacing="0" width="720"><tr><td><pre></>
	<text-after><join(/)pre><join(/)td><join(/)tr><join(/)table>if(ancestor(para),<p>,,)</>
</style>

<style name="SYNOPSIS" group="monodisplay">
	<select>if(attr(format),if(ancestor(synopsis),SYNOPSIS.attr(format).NOBOX,SYNOPSIS.attr(format).BOX),if(ancestor(synopsis),SYNOPSIS.NO.NOBOX,SYNOPSIS.NO.BOX))</>
</style>

<style name="SYNOPSIS.YES.BOX" group="monodisplay">
	<text-before>if(ancestor(para),<p>,,)<table border cellpadding="10" cellspacing="0"><tr><td><pre></>
	<text-after><join(/)pre><join(/)td><join(/)tr><join(/)table><br>if(ancestor(para),<p>,,)</>
</style>

<style name="SYNOPSIS.YES.NOBOX" group="monodisplay">
	<text-before><pre></>
	<text-after><join(/)pre></>
</style>

<style name="SYNOPSIS.NO.BOX" group="monodisplay">
	<text-before>if(ancestor(para),<p>,,)<table border cellpadding="10" cellspacing="0"><tr><td><p><code></>
	<text-after><join(/)code><join(/)p><join(/)td><join(/)tr><join(/)table><br>if(ancestor(para),<p>,,)</>
</style>

<style name="SYNOPSIS.NO.NOBOX" group="monodisplay">
	<text-before><p><code></>
	<text-after><join(/)code><join(/)p></>
</style>


<?INSTED COMMENT: GROUP ol>

<!--	The first ol in a para needs spacing before it.
	See the li element for more info.
  -->
<group name="ol">
	<left-indent>	+=10	</>
	<space-before>	14	</>
	<break-before>	Line	</>
	<text-before>if(ancestor(para),<p>,)<ol></>
	<text-after><join(/)ol></>
</group>

<style name="ORDEREDLIST" group="ol">
	<text-before>if(ancestor(para),<p>,)if(ancestor(orderedlist),if(ancestor(orderedlist,ancestor(orderedlist)),<ol type=i>,<ol type=a>),<ol type=1>)</>
</style>



<?INSTED COMMENT: GROUP p>

<group name="p">
	<space-before>	14	</>
	<break-before>	Line	</>
	<break-after>	Line	</>
	<text-before><p></>
	<text-after><join(/)p></>
</group>

<style name="LEGALNOTICE,PARA" group="p">
</style>

<style name="PARA" group="p">
</style>



<?INSTED COMMENT: GROUP procedure>

<group name="procedure">
</group>

<style name="PROCEDURE" group="procedure">
	<left-indent>	+=10	</>
	<space-before>	14	</>
	<break-before>	Line	</>
	<text-before><h3>Procedure gcnum(me()): if(not(typechild(title)),<join(/)h3><ol>,)</>
	<text-after><join(/)ol></>
</style>

<!-- Procedures took some finagling; notice where h3 and ol open.
  -->
<style name="PROCEDURE,TITLE" group="procedure">
	<font-family>	lucida	</>
	<font-weight>	Bold	</>
	<foreground>	blue3	</>
	<break-before>	Line	</>
	<text-before><!-- h3 already opened by procedure element --></>
	<text-after><join(/)h3><ol></>
</style>

<style name="STEP" group="procedure">
	<left-indent>	+=15	</>
	<first-indent>	-15	</>
	<space-before>	14	</>
	<break-before>	Line	</>
	<text-before><li></>
	<text-after><join(/)li></>
</style>

<style name="SUBSTEPS" group="procedure">
	<left-indent>	+=10	</>
	<space-before>	14	</>
	<break-before>	Line	</>
	<text-before>if(ancestor(substeps),<ol type=1>,<ol type=a>)</>
	<text-after><join(/)ol></>
</style>



<?INSTED COMMENT: GROUP samp>

<group name="samp">
	<foreground>	burlywood4	</>
	<text-before><samp></>
	<text-after><join(/)samp></>
</group>

<style name="ACTION" group="samp">
</style>

<style name="APPLICATION" group="samp">
</style>

<style name="COMPUTEROUTPUT" group="samp">
</style>

<style name="ERRORNAME" group="samp">
</style>

<style name="ERRORTYPE" group="samp">
</style>

<style name="RETURNVALUE" group="samp">
</style>



<?INSTED COMMENT: GROUP seriespara>

<!-- The group seriespara gives space before a paragraph only if it's the
     the first in its series.
  -->
<group name="seriespara">
	<text-before>if(isfirst(),,<p>)</>
	<text-after>if(isfirst(),,<join(/)p>)</>
</group>

<style name="CAUTION,PARA" group="seriespara">
	<text-after>if(isfirst(),if(le(length(content()),85),<br><br><br>,),<join(/)p>)</>
</style>

<style name="FOOTNOTE,PARA" group="seriespara">
	<text-before>if(isfirst(),Footnote gcnum(ancestor(footnote))<p>,<p>)</>
</style>

<style name="IMPORTANT,PARA" group="seriespara">
</style>

<style name="NOTE,PARA" group="seriespara">
</style>

<style name="TIP,PARA" group="seriespara">
</style>

<style name="WARNING,PARA" group="seriespara">
</style>



<?INSTED COMMENT: GROUP suppressed>

<group name="suppressed">
	<hide>	Children	</>
</group>

<style name="CAUTION,TITLE" group="suppressed">
</style>

<style name="COLLECTIONS" group="suppressed">
</style>

<style name="EQUATION" group="suppressed">
	<inline>raster filename="join('eqn', gcnum(), '.gif')"</>
	<select>if(eq(file(join(dir(fig), '/', 'eqn', gcnum(), '.gif')),NONE),EQUATION.NOGIF,EQUATION)</>
</style>

<style name="EQUATION.NOGIF" group="suppressed">
	<text-before><p>[Equation gcnum()] </>
</style>

<style name="INLINEEQUATION" group="suppressed">
	<inline>raster filename="join('inlineeqn', gcnum(), '.gif')"</>
	<select>if(eq(file(join(dir(fig), '/', 'inlineeqn', gcnum(), '.gif')),NONE),INLINEEQUATION.NOGIF,INLINEEQUATION)</></style>

<style name="INLINEEQUATION.NOGIF" group="suppressed">
	<text-before>[Inline equation gcnum()] </>
</style>

<style name="NOTE,TITLE" group="suppressed">
</style>

<style name="TIP,TITLE" group="suppressed">
</style>

<style name="SCREENINFO" group="suppressed">
</style>

<style name="TABLE,TITLE" group="suppressed">
</style>

<style name="WARNING,TITLE" group="suppressed">
</style>



<?INSTED COMMENT: GROUP ul>

<!--	The first list within a paragraph needs space added before it. -->
<group name="ul">
	<left-indent>	+=10	</>
	<space-before>	14	</>
	<break-before>	Line	</>
	<text-before>if(ancestor(para),<p>,)<ul></>
	<text-after><join(/)ul></>
</group>

<style name="ITEMIZEDLIST" group="ul">
</style>



<?INSTED COMMENT: GROUP wrapper>

<!-- 	The wrapper group includes elements whose primary purpose is to 
	contain other elements, usually with little formatting of their own.
  -->
<group name="wrapper">
	<break-before>	Line	</>
</group>

<style name="APPENDIX" group="wrapper">
</style>

<style name="CHAPTER" group="wrapper">
</style>

<style name="DEFLISTENTRY" group="wrapper">
</style>

<style name="EXAMPLE" group="wrapper">
</style>

<style name="PART" group="wrapper">
</style>

<style name="SECTION" group="wrapper">
</style>

<style name="TGROUP" group="wrapper">
</style>

<?INSTED COMMENT: GROUP xrefs>

<group name="xrefs">
	<foreground>	red1	</>
	<score>	Under	</>
	<script>	ebt-link target=idmatch(id, attr(linkend))	</>
</group>

<style name="XREF" group="xrefs">
	<!-- XREF. This style selects an XREF.ELEMENT style based on 
several criteria.

if(xref has xreflabel attribute) 
  then hot-text is xreflabel;
else if(linkend of xref is a title) 
  then select style for linkend's ancestor;
else select style for linkend;

Each style, XREF.ELEMENT, generates customized hot-text, 
tweaking the target of cnum() based on whether linkend is a title
or not.

Element         Hot-text
=======         ========
preface         Preface
appendix        Appendix Z
chapter         Chapter 9
equation        Equation 9
example         Example 9
figure          Figure 9
inlineequation  Inline Equation 9
para            [Click here]
procedure       Procedure 9
section         Section 9.8.7 (see XREF.SECTION for details)
step            Procedure 9, Step 8
table           Table 9
default         [Click here]

Programming note: The select statement breaks unless the DEFAULT item 
of gamut() is protected by join().
-->
	<select>	XREF.if(attr(xreflabel, me()),XREFLABEL,gamut(if(eq(tag(idmatch(attr(linkend))),title), tag(ancestor(idmatch(attr(linkend)))), tag(idmatch(attr(linkend)))), 'appendix chapter equation example figure inlineequation para preface procedure section step table','APPENDIX CHAPTER EQUATION EXAMPLE FIGURE INLINEEQUATION PARA PREFACE PROCEDURE SECTION STEP TABLE', join('DEFAULT')))	</>
</style>

<style name="XREF.APPENDIX" group="xrefs">
	<text-before>Appendix format(gcnum(if(eq(tag(idmatch(attr(linkend))),title), ancestor(idmatch(attr(linkend))), idmatch(attr(linkend)))), LETTER)</>
</style>

<style name="XREF.CHAPTER" group="xrefs">
	<text-before>Chapter gcnum(if(eq(tag(idmatch(attr(linkend))),title), ancestor(idmatch(attr(linkend))), idmatch(attr(linkend))))</>
</style>

<style name="XREF.DEFAULT" group="xrefs">
	<text-before>[Click here]</>
</style>

<style name="XREF.EQUATION" group="xrefs">
	<text-before>Equation gcnum(if(eq(tag(idmatch(attr(linkend))),title), ancestor(idmatch(attr(linkend))), idmatch(attr(linkend))))</>
</style>

<style name="XREF.EXAMPLE" group="xrefs">
	<text-before>Example gcnum(if(eq(tag(idmatch(attr(linkend))),title), ancestor(idmatch(attr(linkend))), idmatch(attr(linkend))))</>
</style>

<style name="XREF.FIGURE" group="xrefs">
	<text-before>Figure gcnum(if(eq(tag(idmatch(attr(linkend))),title), ancestor(idmatch(attr(linkend))), idmatch(attr(linkend))))</>
</style>

<style name="XREF.INLINEEQUATION" group="xrefs">
	<text-before>Inline Equation gcnum(if(eq(tag(idmatch(attr(linkend))),title), ancestor(idmatch(attr(linkend))), idmatch(attr(linkend))))</>
</style>

<style name="XREF.PARA" group="xrefs">
	<text-before>[Click here]</>
</style>

<style name="XREF.PREFACE" group="xrefs">
	<text-before>Preface</>
</style>

<style name="XREF.PROCEDURE" group="xrefs">
	<text-before>Procedure gcnum(if(eq(tag(idmatch(attr(linkend))),title), ancestor(idmatch(attr(linkend))), idmatch(attr(linkend))))</>
</style>

<style name="XREF.SECTION" group="xrefs">
	<!-- XREF.SECTION. Here's a little monster. The enumeration must handle the 
existence of ancestor sections and chapter/appendix/preface. The xref may point to 
either the section or its title.

If there exists       Then add
===============       ========
ancestor preface      Preface
[always]              Section
ancestor chapter      Chapter gcnum().
ancestor appendix     Appendix gcnum().
4-ancestor section    cnum().
3-ancestor section    cnum().
2-ancestor section    cnum().
1-ancestor section    cnum()
if(tag(me) != title)
  1-ancestor section  .
  [always]            cnum(me)
-->
	<text-before>if(ancestor(idmatch(attr(linkend)),preface),Preface Section ,Section )if(ancestor(idmatch(attr(linkend)),chapter),gcnum(ancestor(idmatch(attr(linkend)),chapter)).,)if(ancestor(idmatch(attr(linkend)),appendix),format(gcnum(ancestor(idmatch(attr(linkend)),appendix)),LETTER).,)if(ancestor(idmatch(attr(linkend)),section,4),cnum(ancestor(idmatch(attr(linkend)),section,4)).,)if(ancestor(idmatch(attr(linkend)),section,3),cnum(ancestor(idmatch(attr(linkend)),section,3)).,)if(ancestor(idmatch(attr(linkend)),section,2),cnum(ancestor(idmatch(attr(linkend)),section,2)).,)if(ancestor(idmatch(attr(linkend)),section,1),cnum(ancestor(idmatch(attr(linkend)),section,1)),)if(eq(tag(idmatch(attr(linkend))),title),,if(ancestor(idmatch(attr(linkend)),section,1),.,)cnum(idmatch(attr(linkend))))</>
</style>

<style name="XREF.STEP" group="xrefs">
	<text-before>Procedure gcnum(ancestor(idmatch(attr(linkend)),procedure)), Step cnum(if(eq(tag(idmatch(attr(linkend))),title), ancestor(idmatch(attr(linkend))), idmatch(attr(linkend))))</>
</style>

<style name="XREF.TABLE" group="xrefs">
	<text-before>Table gcnum(if(eq(tag(idmatch(attr(linkend))),title), ancestor(idmatch(attr(linkend))), idmatch(attr(linkend))))</>
</style>

<style name="XREF.XREFLABEL" group="xrefs">
	<text-before>attr(xreflabel,me())</>
</style>



<?INSTED COMMENT: UNGROUPED STYLES FOLLOW>

<style name="#ANNOT">
	<break-before>	Line	</>
</style>

<style name="#DEFAULT">
	<font-family>	times	</>
	<font-weight>	Medium	</>
	<font-slant>	Roman	</>
	<font-video>	Regular	</>
	<font-size>	14	</>
	<line-spacing>	17	</>
</style>

<style name="#FOOTER">
	<text-before><A HREF="http:/docs/help/help_all.html"><img src="/images/help.gif" alt="Help " align=left><join(/)A><A HREF="http:/"><img src="/images/home.gif" alt="Home" align=left><join(/)A><br><br><br><br></>
	<text-after><P><SMALL>Copyright (c) 1998 <A HREF="http://www.cray.com">Cray Research, Inc.<join(/)A><join(/)SMALL></>
</style>


<style name="#HEADER">
	<text-before><join(/)head><body bgcolor="#FFFFFF" text="#000000" ALINK="#ff0000" VLINK="#551a8b" LINK="#0000ee"><img height="72" width="192" src="/images/craylogo.gif" alt="Cray Logo" align="right"> <br> <br> <br></>
</style>



<style name="#QUERY">
	<break-before>	Line	</>
</style>

<style name="#ROOT">
	<break-before>	Line	</>
</style>

<style name="#SDATA">
	<text-before>gamut('trade  mdash  bull','(TM)  --  *',join('&',attr(name).';'))</>
</style>

<style name="#TAGS">
	<font-weight>	Bold	</>
	<foreground>	purple	</>
	<break-before>	Line	</>
</style>

<style name="ACKNOWLEDGEMENTS">
	<break-before>	Line	</>
	<text-before><h2>Notices<join(/)h2></>
</style>

<style name="ALT-TITLE">
	<break-before>	Line	</>
	<break-after>	Line	</>
</style>

<style name="BLOCKQUOTE">
	<left-indent>	+=10	</>
	<space-before>	14	</>
	<break-before>	Line	</>
	<break-after>	Line	</>
	<text-before><blockquote></>
	<text-after><join(/)blockquote></>
</style>

<style name="CITETITLE">
	<foreground>	DarkOrchid2	</>
	<text-before><cite></>
	<text-after><join(/)cite></>
</style>

<style name="CMDSYNOPSIS">
	<break-after>	Line	</>
</style>

<style name="COLSPEC">
	<break-before>	Line	</>
</style>

<style name="COMMENT">
	<hide>  Children  </>
</style>

<style name="COPYRIGHT">
	<break-before>	Line	</>
</style>

<style name="DOCBOOK">
	<font-family>	new century schoolbook	</>
	<font-size>	14	</>
</style>

<style name="EMPHASIS">
	<text-before><b></>
	<text-after><join(/)b></>
</style>

<style name="FOOTNOTE">
	<foreground>	BlueViolet	</>
	<hide>	Children	</>
	<script>	ebt-reveal stylesheet="fullhtml.v" title="Footnote"	</>
	<text-before>[Footnote gcnum()]</>
</style>

<style name="INDEX">
	<hide>	All	</>
</style>

<style name="INDEXTERM">
	<hide>	Children	</>
</style>

<style name="LINEANNOTATION">
	<font-family>	lucida	</>
	<break-before>	Line	</>
	<break-after>	Line	</>
	<text-before><join(/)pre></>
	<text-after><pre></>
</style>

<style name="LINK">
	<font-weight>	Bold	</>
	<foreground>	red3	</>
	<score>	Under	</>
	<break-before>	None	</>
	<text-before> <a href="attr(href)"> </>
	<text-after> join('<','/a>') </>
</style>

<style name="NEWLINE">
	<break-after>	Line	</>
	<text-before>if(ancestor(para),if(content(ancestor(para)),join(' ','<br>'),),join(' ','<br>'))</>
	<text-after>if(ancestor(synopsis),join(' ',' '),)</>
</style>

<style name="PARTNUMBER">
	<text-before><p>SGI Publication Number: </>
	<text-after><join(/)p></>
</style>

<style name="PARTNUMBER,CLASSCODE">
	<text-after>-</>
</style>

<style name="PARTNUMBER,BASE">
	<text-after>-</>
</style>

<style name="PUBNUMBER">
	<text-before><p>Cray Research Publication Number: </>
	<text-after><join(/)p></>
</style>

<style name="PUBNUMBER,PUBTYPE">
	<break-before>	Line	</>
	<text-after>-</>
</style>

<style name="PUBNUMBER,STOCKNUM">
	<text-after> </>
</style>

<style name="PUBTYPE">
	<text-after>-</>
</style>

<style name="REPLACEABLE">
	<text-before><var></>
	<text-after><join(/)var></>
</style>

<style name="REVEND"></style>

<style name="REVNUMBER">
	<space-before>	12	</>
	<break-before>	Line	</>
</style>

<style name="REVST"></style>

<style name="ROW">
	<foreground>	DarkGreen	</>
	<text-before> <tr valign=top> </>
</style>

<!-- 	The simplelist element contains member elements. There are three kinds
	of simplelist, set by the type attribute:
	(i) inline. The members are separated by commas within the line.
	(ii) address. A block address, currently formatted like the default.
	(iii) default. A vertical list, one column only; an indent is given by
	blockquote, and the elements are separated by br. It's assumed the
	members are not longer than a line.
-->
<style name="SIMPLELIST">
	<select>	if(eq(attr(type),inline),SIMPLELIST.INLINE,SIMPLELIST.DEFAULT)	</>
</style>

<style name="SIMPLELIST,MEMBER">
	<select>	if(eq(attr(type,ancestor(simplelist)),inline),SIMPLELIST.MEMBER.INLINE,SIMPLELIST.MEMBER.DEFAULT)	</>
</style>

<style name="SIMPLELIST.DEFAULT">
	<text-before><blockquote></>
	<text-after><join(/)blockquote></>
</style>

<!-- SIMPLELIST.INLINE is just a wrapper. -->
<style name="SIMPLELIST.INLINE">
</style>

<style name="SIMPLELIST.MEMBER.DEFAULT">
	<left-indent>	+=15	</>
	<break-before>	Line	</>
	<text-after>if(islast(),,<br>)</>
</style>

<style name="SIMPLELIST.MEMBER.INLINE">
	<text-before>if(isfirst(),,if(islast(),join(' ')and ,join(',',' ')))</>
</style>

<style name="SUBSCRIPT">
	<text-before><sub></>
	<text-after><join(/)sub></>
</style>

<style name="SUPERSCRIPT">
	<text-before><sup></>
	<text-after><join(/)sup></>
</style>

<style name="TABLE">
	<foreground>	DarkOliveGreen4	</>
	<break-before>	Line	</>
	<text-before><p align=center>Table gcnum(). content(typechild(title))<table cellpadding=10 border=if(eq(attr(frame),'all'),2,0)>if (eq (attr (frame), ALL),,<hr>)</>
	<text-after><join(/)table>if (eq (attr (frame), ALL),,<hr>)</>
</style>

<style name="ROW,ENTRY,PARA">
	<break-after>	Line	</>
	<text-after><br></>
</style>

<style name="TBODY">
	<foreground>	MediumSeaGreen	</>
	<text-before><tbody> </>
</style>

<style name="TBODY,ROW,ENTRY">
	<foreground>	turquoise4	</>
	<select>	if(attr(spanname),TD.SPAN,TD.NOSPAN)	</>
</style>

<style name="TD.NOSPAN">
	<text-before> <td rowspan=incr(attr(morerows))> </>
</style>

<style name="TD.SPAN">
	<text-before> <td cols=incr(sub(cnum(attrchild(colname,attr(nameend,                  attrchild(spanname,attr(spanname),ancestor(tgroup))),                  ancestor(tgroup))),cnum(attrchild(colname,attr(namest,                  attrchild(spanname,attr(spanname),ancestor(tgroup))),                  ancestor(tgroup))))) rowspan=incr(attr(morerows))> </>
</style>

<style name="TFOOT">
	<text-before> <tfoot> </>
</style>

<style name="TFOOT,ROW,ENTRY">
	<select>	if(attr(spanname),TH.SPAN,TH.NOSPAN)	</>
</style>

<style name="TH.NOSPAN">
	<foreground>	ForestGreen	</>
	<text-before><td valign=bottom rowspan=incr(attr(morerows))> </>
	<text-after>if(eq(attr(frame,ancestor(table)),ALL),,<hr>)</>
</style>

<style name="TH.SPAN">
	<text-before><td valign=bottom cols=incr(sub(cnum(attrchild(colname,attr(nameend,attrchild(spanname,attr(spanname),ancestor(tgroup))),ancestor(tgroup))),cnum(attrchild(colname,attr(namest,attrchild(spanname,attr(spanname),ancestor(tgroup))),ancestor(tgroup))))) rowspan=incr(attr(morerows))> </>
	<text-after>if(eq(attr(frame,ancestor(table)),ALL),,<hr>)</>
</style>

<style name="THEAD">
	<foreground>	DarkGreen	</>
	<text-before><thead></>
</style>

<style name="THEAD,ROW,ENTRY">
	<select>	if(attr(spanname),TH.SPAN,TH.NOSPAN)	</>
</style>

<style name="TOC">
	<hide>	Off	</>
</style>

</sheet>
