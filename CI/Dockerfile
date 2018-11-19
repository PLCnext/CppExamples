# Docker Container with PLCNext SDK installed
FROM build_image:latest 
#
MAINTAINER OW <owarneke@phoenixcontact.com>


ENV PLCNCLI /CLI/plcncli
ENV SDKs /opt/pxc/
ENV CONTAINER /container
ENV PathToCLI "/CLI/plcncli"


ENV projectName "ProgramComponentInteraction"
ENV targetName "AXCF2152"
ENV targetVersion "2.0.3.86"
ENV build "build"

WORKDIR /wrk
COPY CI /wrk/CI


COPY Examples/$projectName /wrk/build/
# Execute Build Process
CMD ["/bin/sh", "-c","./CI/Compile.sh"]
