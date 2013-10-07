<?php
/*
$currencies = array(
    "AUDJPY" => 1175270400, // starting from 2007.03.30 16:00
    "AUDNZD" => 1229961600, // starting from 2008.12.22 16:00
    "AUDUSD" => 1175270400, // starting from 2007.03.30 16:00
    "CADJPY" => 1175270400, // starting from 2007.03.30 16:00
    "CHFJPY" => 1175270400, // starting from 2007.03.30 16:00
    "EURAUD" => 1175270400, // starting from 2007.03.30 16:00
    "EURCAD" => 1222167600, // starting from 2008.09.23 11:00
    "EURCHF" => 1175270400, // starting from 2007.03.30 16:00
    "EURGBP" => 1175270400, // starting from 2007.03.30 16:00
    "EURJPY" => 1175270400, // starting from 2007.03.30 16:00
    "EURNOK" => 1175270400, // starting from 2007.03.30 16:00
    "EURSEK" => 1175270400, // starting from 2007.03.30 16:00
    "EURUSD" => 1175270400, // starting from 2007.03.30 16:00
    "GBPCHF" => 1175270400, // starting from 2007.03.30 16:00
    "GBPJPY" => 1175270400, // starting from 2007.03.30 16:00
    "GBPUSD" => 1175270400, // starting from 2007.03.30 16:00
    "NZDUSD" => 1175270400, // starting from 2007.03.30 16:00
    "USDCAD" => 1175270400, // starting from 2007.03.30 16:00
    "USDCHF" => 1175270400, // starting from 2007.03.30 16:00
    "USDJPY" => 1175270400, // starting from 2007.03.30 16:00
    "USDNOK" => 1222639200, // starting from 2008.09.28 22:00
    "USDSEK" => 1222642800, // starting from 2008.09.28 23:00
    "USDSGD" => 1222642800, // starting from 2008.09.28 23:00
    "AUDCAD" => 1266318000, // starting from 2010.02.16 11:00
    "AUDCHF" => 1266318000, // starting from 2010.02.16 11:00
    "CADCHF" => 1266318000, // starting from 2010.02.16 11:00
    "EURNZD" => 1266318000, // starting from 2010.02.16 11:00
    "GBPAUD" => 1266318000, // starting from 2010.02.16 11:00
    "GBPCAD" => 1266318000, // starting from 2010.02.16 11:00
    "GBPNZD" => 1266318000, // starting from 2010.02.16 11:00
    "NZDCAD" => 1266318000, // starting from 2010.02.16 11:00
    "NZDCHF" => 1266318000, // starting from 2010.02.16 11:00
    "NZDJPY" => 1266318000, // starting from 2010.02.16 11:00
    "XAGUSD" => 1289491200, // starting from 2010.11.11 16:00
    "XAUUSD" => 1305010800, // starting from 2011.05.10 07:00
    );
*/

require 'currencies.php';

$missingfilecount = 0;/*�������ϲ����ڵ��ļ�����*/
$failedfilecount = 0;/*������;������ļ�����*/
$successfilecount = 0;/*�������ص��ļ�����*/
$skippedfilecount = 0;/*�����Ѿ����ڣ����������ļ�����*/
$quitstring = "����";

$lasttime = 0;/*ÿ������ĳһ��ĵ�һ���ļ�ǰ��¼��ǰGMTʱ��*/
$lastday = 0;/*����ǰһ���Day��*/

/*��ȡ����ʾ��ǰ��GMTʱ��*/
$curtime = time();
error("Current GMT time:".gmstrftime("%m/%d/%Y %H:%M:%S",$curtime)."\r\n");

/*��ÿһ�����ҶԽ���ѭ�����أ���ǰ�汾currencies.php��������һ�����Ҷ�*/
foreach($currencies as $pair => $firsttick) {

    $firsttick -= $firsttick % 3600;
    error("Info: Downloading $pair starting with ".gmstrftime("%m/%d/%Y %H:%M:%S",$firsttick)."\r\n");

	/*������ظ����ļ���ÿ���ļ�����һ��Сʱ��tick����*/
    for($i = $firsttick; $i < $curtime-3600; $i += 3600) {
        $year = gmstrftime('%Y',$i);
        $month = str_pad(gmstrftime('%m',$i) - 1, 2, '0', STR_PAD_LEFT); /*��ʽ��(month-1)������ 1�·���ת��Ϊ 00�� 2�·�-> 01 */
        $day = gmstrftime('%d',$i);
        $hour = gmstrftime('%H',$i);
        $url = "http://www.dukascopy.com/datafeed/$pair/$year/$month/$day/{$hour}h_ticks.bi5";

		/*����ʼ����ĳһ��ĵ�һ���ļ�ǰ��$lasttim, $lastday����¼��������ʵ������ʾ���ص���һ�죬������ʵ�����á�*/
		if ($day != $lastday)
		{
			/*�������ǰһ���BIN������3���ھͱ�������ϣ���Ϊǰһ��������Ѿ�������*/
			if (time() - $lasttime < 3)
			{
				//error("BIN data already downloaded. Skipped.\r\n");
			}

			$lasttime = time();
			$lastday = $day;
			echo("Info: Downloading BIN data of $pair- ".gmstrftime("%m/%d/%Y",$i)."\r\n");
		}

		/*���㱾�ش洢·��*/
        $localpath = "$pair/$year/$month/$day/";
        $binlocalfile = $localpath . $hour . "h_ticks.bin";
        $localfile = $localpath . $hour . "h_ticks.bi5";
        if (!file_exists($localpath)) {
            mkdir($localpath, 0777, true);
        }

		/*���������ļ�������ʱ�����������*/
        if (!file_exists($localfile) && !file_exists($binlocalfile)) {
            $ch = FALSE;
            $j = 0;

			/*���޷����ӷ������������������أ���ೢ������*/
            do {
                if ($ch !== FALSE) {
                    curl_close($ch);
                }
                $ch = curl_init($url);
                curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
                curl_setopt($ch, CURLOPT_BINARYTRANSFER, true);
                curl_setopt($ch, CURLOPT_HEADER, 0);
                $result = curl_exec($ch);
                $j++;
            } while ($j <= 3 && curl_errno($ch));

			/*����������Ȼ�޷����ӷ��������˳�����. */
            if (curl_errno($ch)) {
                error("FATAL: Couldn't download $url.\r\nError was: ".curl_error($ch)."\r\n");
				$quitstring = "�޷����ӷ�����";
                exit(1);
            }
			/*���������������ݣ����ǲ���һ���������سɹ�*/
            else {

				/*����������404���룬��ʾ��Ҫ���ص��ļ�������*/
                if (curl_getinfo($ch, CURLINFO_HTTP_CODE) == 404) {
                    $weekday = gmstrftime('%a',$i);
                    if (strcasecmp($weekday,'sun') == 0 || strcasecmp($weekday,'sat') == 0) {
                        /*missing file������ĩ����*/
                        error("Info: missing weekend file $url\r\n");
                    }
                    else {
                        error("WARNING: missing file $url ($i - ".gmstrftime("%m/%d/%Y %H:%M GMT",$i).")\r\n");
                    }

					$missingfilecount++;
                }
				/*����������200���룬��ʾ�ļ�����������*/
                else if (curl_getinfo($ch, CURLINFO_HTTP_CODE) == 200) {
                    $outfd = fopen($localfile, 'wb');
                    if ($outfd === FALSE) {
                        error("FATAL: Couldn't open $localfile ($url - $i)\r\n");
						$quitstring = "���������ļ�����";
                        exit(1);
                    }
                    fwrite($outfd, $result);
                    fclose($outfd);
                    //error("Info: successfully downloaded $url\r\n");
					$successfilecount++;
                }
				/*δ֪�ķ��غ��룬��ʾ�ļ����س�δ֪����*/
                else {
                    error("WARNING: did not download $url ($i - ".gmstrftime("%m/%d/%Y %H:%M GMT",$i).") - error code was ".curl_getinfo($ch, CURLINFO_HTTP_CODE)."\r\nContent was: $result\r\n");

					$failedfilecount++;
                }
            }
            curl_close($ch);
        }
        else {
			/*�����ļ��Ѿ����ڣ�ֱ��������������߼���֤�����ص�ÿ���ļ����������ġ�*/
            //error("Info: skipping $url, local file already exists.\r\n");
			$skippedfilecount++;
        }

		/*�������һ���ļ������أ�����������һ���ļ�*/

    }

	$totalseconds = time() - $curtime;

	error("�Ѿ����".$pair."���������� ����ʹ��". outtm($totalseconds)."���˳�ʱ��״̬Ϊ:".$quitstring."��\r\n");
	error("����".$successfilecount."���ļ��ڱ��������б����ء�\r\n��".$skippedfilecount."���ļ������Ѿ����ڶ���������\r\n");
	error("��".$missingfilecount."���ļ��ڷ�������ȱʧ��δ�����ء�\r\n��".$failedfilecount."���ļ������ع����г���δ֪�����δ�ܱ����κ����ݡ�\r\n");


	/*�������һ�����Ҷ������ļ������ص����أ�����������һ�����Ҷԡ���ǰ�汾���ǽ�������һ�Ի��Ҷԣ���ʹ��break����ѭ����ʵ�ʽ�������*/
	break;
}



function error($error) {
    echo $error;
    $fd = fopen('error.log', 'a+');
    fwrite($fd, $error);
    fclose($fd);
}


/*
���ݾ������������س� �죺Сʱ�����ӣ���ĸ�ʽ��
*/

function outtm($sec){
	$d = floor($sec / 86400);
	$tmp = $sec % 86400;
	$h = floor($tmp / 3600);
	$tmp %= 3600;
	$m = floor($tmp /60);
	$s = $tmp % 60;
	return "[".$d."��".$h."Сʱ".$m."��".$s."��]";
}
