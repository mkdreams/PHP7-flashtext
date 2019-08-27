## 功能介绍
在大量关键词情况下，匹配一段文字中包含哪些关键词，使用flashtext速度上会有很大的提升。实际应用场景：
- 监控整个网站关键词，比如出现某种事件、博彩暗链等。
- solr等分词工具搜索出结果需要反拿关键词。

## 目录说明
docs-文档相关资源  
phpsrc-PHP版本（真实项目中已使用过）  
.-C++扩展代码（效果不理想，执行时间太长，C++功底还不足）  

## 性能测试
- 5000字文章，重复执行100次所用时间
- preg版本测试代码
```
//$words 为关键词数量
//$content 为正文
foreach($words as $word) {
    preg_match('/'.preg_quote($word).'/i', $content);
}
```

![avatar](https://github.com/chenlincolin/PHP7-flashtext/blob/master/docs/flashtext%20performance%20test%2020190827.png)

## 相关项目
- [python flashtext](https://github.com/vi3k6i5/flashtext)
