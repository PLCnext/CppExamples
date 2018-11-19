 #!/bin/bash
ProjectName=$1
TargetName=$2
TargetVersion=$3
ExportTo=$4
echo $1 $2 $3 $4

mkdir ~/Library_Releases/${ProjectName}
mkdir /mnt/hgfs/Shared\ Folder/Library_Release
if docker build \
		-t 'build-environment-and-sources' \
		-f 'CI/Dockerfile' \
		. ;
then
	if docker run \
		-e projectName=${ProjectName} \
		-e targetName=${TargetName} \
		-e targetVersion=${TargetVersion} \
		-e sourceFiles='src' \
		--name 'compiled-code' \
		build-environment-and-sources ;
	then
    	echo "building succeeded"
		if docker cp compiled-code:/wrk/build/ /mnt/hgfs/Shared\ Folder/Library_release || 
			docker cp compiled-code:/wrk/build/* ~/Library_Releases/${ProjectName}  ;then
			echo "export Successfull"
			docker rm compiled-code
		else
			docker rm compiled-code
			echo "export Failed"
   		fi
	else
   	docker rm compiled-code
   	 echo "Running container compiled-code / Compile Failed"
	fi
else
 docker rm build-environment-and-sources
  echo "building ${ProjectName}-build-environment-and-source Container failed "
fi
