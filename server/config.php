<?php

$db_server   = "localhost";
$db_username = "";
$db_password = "";
$db_database = "";

$builds_aws_access_key      = getenv("ps_builds_aws_access_key");
$builds_aws_access_secret   = getenv("ps_builds_aws_access_secret");
$builds_aws_region          = getenv("ps_builds_aws_region");
$builds_dynamodb_table_name = getenv("ps_builds_dynamodb_table_name");

$compat_aws_region          = getenv("ps_compat_aws_region");
$compat_s3_bucket_name      = getenv("ps_compat_s3_bucket_name");

$gh_apitoken = getenv("ps_gh_apitoken");

if(file_exists("config_override.php"))
{
	include("config_override.php");
}

?>
