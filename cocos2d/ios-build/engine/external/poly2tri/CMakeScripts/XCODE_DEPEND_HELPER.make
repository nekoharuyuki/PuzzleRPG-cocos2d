# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.ext_poly2tri.Debug:
/Users/nekoharuyuki/Documents/PuzzleRPG/cocos2d/ios-build/lib/Debug/libext_poly2tri.a:
	/bin/rm -f /Users/nekoharuyuki/Documents/PuzzleRPG/cocos2d/ios-build/lib/Debug/libext_poly2tri.a


PostBuild.ext_poly2tri.Release:
/Users/nekoharuyuki/Documents/PuzzleRPG/cocos2d/ios-build/lib/Release/libext_poly2tri.a:
	/bin/rm -f /Users/nekoharuyuki/Documents/PuzzleRPG/cocos2d/ios-build/lib/Release/libext_poly2tri.a


PostBuild.ext_poly2tri.MinSizeRel:
/Users/nekoharuyuki/Documents/PuzzleRPG/cocos2d/ios-build/lib/MinSizeRel/libext_poly2tri.a:
	/bin/rm -f /Users/nekoharuyuki/Documents/PuzzleRPG/cocos2d/ios-build/lib/MinSizeRel/libext_poly2tri.a


PostBuild.ext_poly2tri.RelWithDebInfo:
/Users/nekoharuyuki/Documents/PuzzleRPG/cocos2d/ios-build/lib/RelWithDebInfo/libext_poly2tri.a:
	/bin/rm -f /Users/nekoharuyuki/Documents/PuzzleRPG/cocos2d/ios-build/lib/RelWithDebInfo/libext_poly2tri.a




# For each target create a dummy ruleso the target does not have to exist
