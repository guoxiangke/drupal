<?php
/**
 * @author dale
 * @version $Id$
 * @copyright dale
 * @package sina
 */
/**
 * 圣经导航
 */
function bible_books_index(){
	$sql = "select * from {bible_index}";
	//$sql = "select * from {users}";
	$query = db_query($sql);
	$output = '<style type="text/css">
</style>
	<div id="bibles_content" class="b-warp clear-fix">
		<div class="b-top">
			<h1>圣经卷导航</h1>
			<div class="b-maiqin">直达麦琴每日读经</div>
			<div class="b-nav_to">跳转到：新约|旧约|卷书|章节</div>
		</div>
			<div class="b-content clear-block">
				<ul class="b-lists">';
	$count=0;
	foreach ($query as $result) {//= db_fetch_object($query)
		$new_class=null;
		if($result->volume==40) $new_class="b-New";
	 $output .= '
					<li class="b-v-item '.$new_class.'"><span class="bc-grey">'.$result->volume.'</span>'.l($result->c_name,'bible/'.$result->volume.'/1/CUV').'</li>
				';
	$count++;
	}
	$output .= '</ul>
			</div>
		<div class="clear"></div>
	</div>';
	return $output;
}
function bible_volumes_index($volume){
	$sql = "select v_total from {bible_index} where volume = $volume";
	$v_total = db_result(db_query($sql));
	$output = '<style type="text/css">
	.b-warp,.b-top,.b-sidebar,.b-title{
		border:1px solid #666;
		padding:10px;
		}
	.b-top{
    margin: 0 auto;
    text-align: center;}
	.b-item{width:13%;float:left;}
	
	#bibles_content{font-family:Microsoft YaHei;font-weight:bold;}
	#bibles_content a:link, #bibles_content a:visited {
	    color: #0099FF;
	    text-decoration: none;
	}
	#bibles_content a:hover {
		    color: #0099FF;
		    text-decoration: underline;
		}
	#bibles_content .b-New a:link{color:#FF00FF;}
	.bc-grey{color:gray;font-weight:normal;}
</style>
	<div id="bibles_content" class="b-warp clear-fix">
		<div class="b-top">
			<h1>圣经卷导航</h1>
			<div class="b-maiqin">直达麦琴每日读经</div>
			<div class="b-nav_to">跳转到：新约|旧约|卷书|章节</div>
		</div>
			<div class="b-content clear-block">
				<ul class="b-lists">';
	for($i=1;$i<=$v_total;$i++){
	 $output .= '
					<li class="b-item"><span class="bc-grey">'.l($i,'bible/'.$volume.'/'.$i.'/CUV').'</span></li>';
	
	}
	$output .= '</ul>
			</div>
		<div class="clear"></div>
	</div>';
	return $output;
}
function bible_page($volume,$chapter='1',$version='CUV'){
		switch ($version) {
			case 'CUV':
				$table = 'bible_zh_cuv';
				break;
			case 'NIV':
				$table = 'bible_niv';
				break;
			case 'KJV':
				$table = 'bible_kjv';
				break;
			
			default:
				$table = 'bible_zh_cuv';
				break;
		}//select * from bible_zh_cuv  where Book = 01 AND Verse like '1:%'
		$sql = "select * from $table where Book = $volume AND verse like '$chapter:%' ";
		//$sql = "select * from {users}";
		$query = db_query($sql);
		
		$sql = "select * from {bible_index} where volume = $volume";
		$bible_indexs = db_query($sql)->fetchAll();
		foreach ($bible_indexs as $value) {//只有一条记录
			$v_abb = $value->v_abb;//卷缩写
			$v_total = $value->v_total; //总卷数
			$c_name = $value->c_name;//总卷数
			$volume = $value->volume;
			$e_name = $value->e_name;
		}	
		if($v_total==$chapter){
			$next_volume = $volume+1;			
			if($next_volume<10)
			{$next_chapter_url = "0$next_volume/1";}
			else{$next_chapter_url = "0$next_volume/1";}
		}else{
			$next_chapter = $chapter+1;
			$next_chapter_url = "$volume/$next_chapter";
		} 
		if(1==$chapter){//上一卷的最后一章
			$pre_volume = $volume-1;
			$sql = "select v_total from {bible_index} where volume = $pre_volume";
			$pre_volume_v_total =  db_query($sql)->fetchField();
			//$count = db_select('node')->condition('type', $type)->countQuery()->execute()->fetchField();
			$pre_chapter_url = "$pre_volume/$pre_volume_v_total";
		}else{
			$pre_chapter = $chapter-1;
			$pre_chapter_url = "$volume/$pre_chapter";
		} 
		$output = '<style type="text/css">
		
	</style>
		<div id="bibles_content" class="b-warp clear-fix">
			<div class="b-top">
				<h1>'.l('圣经卷导航','bible').'</h1>
				<div class="b-maiqin">直达麦琴每日读经</div>
				<div class="b-nav_to">跳转到：新约|旧约|卷书|章节</div>
				

				<span class="Home chapter" id="toggle_index"><a name="index">'.$c_name.'</a>(折叠章目录↑)</span>
				<div class="c-index" id="c_index">';
				for($i=1;$i<=$v_total;$i++){
					if($i==$chapter) $active_class = "current-chapter";
					
				$output .= '
					<span class="bc-grey line-10" id="'.$active_class.'">'.l($i,'bible/'.$volume.'/'.$i.'/CUV').'</span>';
				$active_class='';
				}
				$output.='
				<div class="clear"></div>
				</div>
				<div class="clear"></div>
				<div class="b-nav_to-chapter">
				';
				$mp3_url = 'http://www.fuyin.com/audios/mp3/bbn/'.$volume.'_'.strtolower($e_name).($chapter>9?$chapter:('0'.$chapter)).'.mp3';
				if($volume==19)
				$mp3_url = 'http://www.fuyin.com/audios/mp3/bbn/'.$volume.'_psalms'.(str_pad($chapter,3,'0',STR_PAD_LEFT)).'.mp3';
				$mp3_url = urlencode($mp3_url);
				$output .= '<div id="audio_player"><embed type="application/x-shockwave-flash" width="290" height="24" 

src="'.drupal_get_path('module','bibles').'/3.swf?

soundFile='.$mp3_url.'&amp;bg=0xCDDFF3&amp;leftbg=0x357DCE&amp;lefticon=0xF2F2F2&amp;rightbg=0x357DCE&amp;righ

tbghover=0x4499EE&amp;righticon=0xF2F2F2&amp;righticonhover=0xFFFFFF&amp;text=0x357DCE&amp;slider=

0x357DCE&amp;track=0xFFFFFF&amp;border=0xFFFFFF&amp;loader=0x8EC2F4&amp;autostart=yes&amp;loop=no" 

wmode="transparent" quality="high"></div>';
				if($volume==1&&$chapter==1){
					$output.='<span class="pre chapter">《上一章</span>';
				}else{
					$output.='<span class="pre chapter">'.l('《上一章','bible/'.$pre_chapter_url.'/CUV').'</span>';
				}
				
				if($volume==66&&$chapter==22){
							$output.='<span class="next chapter">下一章》</span>';
				}else{
							$output.='<span class="next chapter">'.l('下一章》','bible/'.$next_chapter_url.'/CUV').'</span>';
				}
			
				$output.='	
				</div>
			</div>
				<div class="b-content clear-block">
					<ul class="b-lists">';
		$count = 1;
		foreach ($query as $result) {
		 $output .= '
						<li class="b-item">
						<span class="source">
						'.$v_abb.$chapter.':'.$count.'
						</span>
						<span class="bc-grey">'.($result->TextData?$result->TextData:'--同上节').'</span>
						</li>
					';
		 $count++;
		}
		$output .= '</ul>
				</div>
				<div class="bottom-nav">';
				
				if($volume==1&&$chapter==1){
					$output.='<span class="pre chapter">《上一章</span>';
				}else{
					$output.='<span class="pre chapter">'.l('《上一章','bible/'.$pre_chapter_url.'/CUV').'</span>';
				}
					
					$output.='<span class="Home chapter"><a href="#index">回目录</a></span>';
					
				if($volume==66&&$chapter==22){
							$output.='<span class="next chapter">下一章》</span>';
				}else{
							$output.='<span class="next chapter">'.l('下一章》','bible/'.$next_chapter_url.'/CUV').'</span>';
				}
				$output.='	
				</div>
			<div class="clear"></div>
		</div>';
		$output .= '<!-- UY BEGIN -->
<div id="uyan_frame"></div>
<script type="text/javascript" id="UYScript" src="http://v1.uyan.cc/js/iframe.js?UYUserId=91212" async=""></script>
<!-- UY END --><!-- UJian Button BEGIN -->
<script type="text/javascript" src="http://v1.ujian.cc/code/ujian.js?type=slide&uid=91212"></script>
<!-- UJian Button END -->';
		return $output;
}