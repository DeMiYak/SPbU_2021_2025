<?php
$sonnet76 = <<<HERE
<pre>
Sonnet # 76, William Shakespeare

Why is my verse so barren of new pride,
so far from variation or quick change?
Why with the time do I not glance aside
To new-found methods and to compounds strange?
Why write I still all one, ever the same
And keep invention in a noted weed
That every word doth almost tell my name
Showing their birth, and where they did proceed?
O, know sweet love I always write of you
And you and love are still my argument;
So all my best is dressing old words new
Spending again what is already spent;
For as the sun is daily new and old
So is my love still telling what is told.
</pre>
HERE;

$fp = fopen("sonnet76.txt", "w");
fputs($fp, $sonnet76);
fclose($fp);
?>