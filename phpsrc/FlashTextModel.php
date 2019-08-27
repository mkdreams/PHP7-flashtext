<?php
class FlashTextModel{
    public $tree;
    public function treeArr($array) {
        foreach($array as $key => $string) {
            $strlen = mb_strlen($string,"utf8");
            
            $tree = &$this->tree;
            for($i=0;$i<$strlen;$i++) {
                $oneWord = mb_substr($string, $i,1);
                if (!isset($tree[$oneWord])) {
                    $tree[$oneWord] = [];
                }
                $tree = &$tree[$oneWord];
            }
            $tree['_v'] = $key;
        }
        
        return $this->tree;
    }
    
    public function getKeyIndex($sContent,$holdCronModel) {
        $strlen = mb_strlen($sContent,"utf8");
        $nowTree = [];
        $result = [];
        $oneWordArr = preg_split('//u', $sContent, null, PREG_SPLIT_NO_EMPTY);
        foreach ($oneWordArr as $oneWord) {
            $nowTreeTemp = [];
            foreach ($nowTree as $nowTreeIndex => $now) {
                //next 匹配
                if(isset($now[$oneWord])) {
                    $nowTreeTemp[] = $now[$oneWord];//枝叶下一级
                }
                
                if(isset($nowTree[$nowTreeIndex]['_v'])) {
                    $result[] = $nowTree[$nowTreeIndex]['_v'];
                }
            }
            $nowTree = $nowTreeTemp;
            
            //第一个匹配
            if(isset($this->tree[$oneWord])) {
                $nowTree[] = $this->tree[$oneWord];
            }
        }
        
        return $result;
    }
}