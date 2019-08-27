<?php
//var_dump(flashtext(["mma",1134,1231, 42.33, "jjj","中國人","是","我"],"我mma1231是中國人111"));
$o = new flashtext();
$o->learn(["mma",1134,1231, 42.33, "jjj","中國人","是","我"]);
var_dump($o->match("我mma1231是中國人111"));
