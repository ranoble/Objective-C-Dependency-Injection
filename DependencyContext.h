//
//  DependencyContext.h
//  MacmillanCatalog
//
//  Created by Richard Noble on 18/11/2010.
//  Copyright 2010 TangentLabs. All rights reserved.
//

//Usage: 
//
//Like standard DI you will need to define a protocol (interface for the java minded) and one or more implementations.
//
//Next you will need to define a dependencies file named dependencies.plist in your resources
//use the key column for your Service and the value as a String the implementation you wish to inject.
//
//include DependencyContext.h in any files that you wish to use access the dependencies for.
//
//From here on in you can access any service using the [[DependencyContext sharedInstance] getDependency: __SERVICESTRING__] call.
//
//Autowiring - can be improved: 
//
//Do as above; then create a property in the header file you plan to use. 
//IE: id<Service> servicePropertyName; 
//Next define the property further as @property(getter=[get[Service], readonly) id<Service> servicePropertyName;
//
//lastly in your implementation call the macro AUTO_WIRE([Service], @"[Service]") where service is the name of the service.
//
//now you can use the injected service as a standard (readonly) property



#import <Foundation/Foundation.h>
#import "SynthesizeSingleton.h"

#define AUTO_WIRE(__CLASSNAME__, __SERVICESTRING__)	\
- (id)get##__CLASSNAME__		\
{	\
return [[DependencyContext sharedInstance] getDependency: __SERVICESTRING__]; \
}

@interface DependencyContext : NSObject {
	//We use this to store all already instantiated object
	NSMutableDictionary* objectDictionary;
	
	NSMutableDictionary* classDefinitionDictionary;
	
}

SYNTHESIZE_SINGLETON_FOR_CLASS_HEADER(DependencyContext);

@property (nonatomic, retain) NSMutableDictionary* objectDictionary;
@property (nonatomic, retain) NSMutableDictionary* classDefinitionDictionary;

-(id) getDependency: (NSString*) dependencyProtocol;
-(NSBundle*) getBundle;

+ (DependencyContext*) sharedInstance;
+ (void) purgeSharedInstance;

@end

