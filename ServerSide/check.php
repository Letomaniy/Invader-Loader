	<?php
	date_default_timezone_set("Europe/Moscow");
	$link = mysqli_connect("", "", ""); // "host", "username", "password"
	$database = mysqli_select_db($link, ""); //DATABASE
	$data = "";
	if ($_GET['data'] == NULL)
	{
		$data = $_POST['data'];
	}
	else
	{
		$data = $_GET['data'];
	}
	$tables = "users"; //tables
	$dec_Data = str_replace("c11ce8c670b55204d00e4a61ff9c79", "", $data);
	$dec_Data = Decrypt($dec_Data, "c526fce0e4e706322424de071b0e0d");
	list($hash_int, $user, $pword, $key, $hwid) = explode("|", $dec_Data);
	$sql = "SELECT * FROM " . $tables . " WHERE username = '" . mysqli_real_escape_string($link, $user) . "'"; // /////////////////////////////////
	$result = $link->query($sql); // /////////////////////////////////

	$loginCorrect;
	$loginIncorrect ;
	$keyCorrect;
	$keySystemOFF;
	$keyIncorrect;
	$hwidCorrect;
	$hwidIncorrect;
	$hwidSet;
	$passwordCorrect;
	$passwordIncorrect ;
$isDays;
	$Hash = md5($hash_int);
	if ($result->num_rows > 0)
	{ 
		while ($row = $result->fetch_assoc())
		{
			if($row['days'] <= 0)
			{
				$isDays = "UijeSR";//Days is gone
			}else
			{
				$isDays = "2zihdc";//Good game!
			}
			if ($row['username'] == $user)
			{
				//правильный логин
				$loginCorrect = "3DOm";
			}
			else
			{
				//неправильный логин
				$loginIncorrect = "Tvvh";
			}
			if ($row['public_key'] == $key && !contains($key, "NOACTIVEKEYSYSTEM"))
			{
				//Возвращение о правильности ключа
				$keyCorrect = "AXqEK7";
			}
			else if ($row['public_key'] != $key)
			{
				if (contains($key, "NOACTIVEKEYSYSTEM"))
				{
					//ключ отключён
					$keySystemOFF = "NOACTIVEKEYSYSTEM";
				}
				else
				{
					//ключ неверный
					$keyIncorrect = "gpXShU";
				}
			}
			if (strlen($row['hwid']) > 1)
			{
				if ($row['hwid'] == $hwid)
				{
					//hwid правильный
					$hwidCorrect = "6MDp";

				}
				else
				{
					//hwid не правильный
					$hwidIncorrect = "nBIM";
				}
			}
			else
			{
				$sql = "UPDATE " . $tables . " SET hwid='$hwid'  WHERE username='$user'";
				if (mysqli_query($link, $sql))
				{
					//установка hwid
					$hwidSet = "siAa";

				}

			}
			if ($row['password'] == $pword)
			{
				//пароль верный
				$passwordCorrect = "6MDM";
			}
			else
			{
				//пароль не верный
				$passwordIncorrect = "Eb9k";
			} 
		}
		if (strlen($user) > 1)
		{
			$ip = $_SERVER['REMOTE_ADDR'];
			$ip_set = "UPDATE " . $tables . " SET ip='$ip'  WHERE username='$user'";
			mysqli_query($link, $ip_set);
			$timeSet = date('Y-m-d H:i:s');
			$timeSet_ = "UPDATE " . $tables . " SET lastUpdate='$timeSet'  WHERE username='$user'";
			mysqli_query($link, $timeSet_);
		}
	   echo "izwhHrDONzDKDSNo5Iac8qUPbcniD1u4nSVvZn0fwaRu9" . base64_encode(generateRandomString(10). "$keySystemOFF$Hash".generateRandomString(10)."$loginCorrect".generateRandomString(10)."$loginIncorrect".generateRandomString(10)."$keyCorrect".generateRandomString(10)."$isDays$keyIncorrect".generateRandomString(10)."$hwidCorrect".generateRandomString(10)."$hwidIncorrect".generateRandomString(10)."$hwidSet".generateRandomString(10)."$passwordCorrect".generateRandomString(10)."$passwordIncorrect".generateRandomString(10));
	}

	function Encrypt($strInput, $strPassword)
	{
		$strOutput;
		$baInput = byteStr2byteArray($strInput);
		$baPassword = byteStr2byteArray($strPassword);

		for ($i = 0;$i < count($baInput);$i++)
		{
			for ($j = 0;$j < count($baPassword);$j++)
			{
				$baInput[$i] = $baInput[$i] ^ ($baPassword[$j] + ($i * $j));
			}
			$strOutput .= str_pad(dechex((int)$baInput[$i]) , 2, "0", STR_PAD_LEFT);
		}
		return $strOutput;
	}

	function contains($needle, $haystack)
	{
		return strpos($haystack, $needle) !== false;
	}

	function Decrypt($strInput, $strPassword)
	{
		$baInput = byteStr2byteArray(hexToStr($strInput));
		$baPassword = byteStr2byteArray($strPassword);

		for ($i = 0;$i < count($baInput);$i++)
		{
			for ($j = 0;$j < count($baPassword);$j++)
			{
				$baInput[$i] = $baInput[$i] ^ ($baPassword[$j] + ($i * $j));
			}
		}
		$strings = array_map("chr", $baInput);
		$string = implode($strings);
		return $string;
	}

	function byteStr2byteArray($s)
	{
		return array_slice(unpack("C*", "\0" . $s) , 1);
	}

	function strToHex($string)
	{
		$hex = '';
		for ($i = 0;$i < strlen($string);$i++)
		{
			$hex .= dechex(ord($string[$i]));
		}
		return $hex;
	}

	function hexToStr($hex)
	{
		$string = '';
		for ($i = 0;$i < strlen($hex) - 1;$i += 2)
		{
			$string .= chr(hexdec($hex[$i] . $hex[$i + 1]));
		}
		return $string;
	}
	function generateRandomString($length = 10)
	{
		$characters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
		$charactersLength = strlen($characters);
		$randomString = '';
		for ($i = 0;$i < $length;$i++)
		{
			$randomString .= $characters[rand(0, $charactersLength - 1) ];
		}
		return $randomString;
	}
	?>
