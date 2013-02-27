#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <objc/runtime.h>

#define OUTFILE_LOCATION "/tmp/objc_rt_class_dump.txt"

extern int _objc_rtClassDump(void) __attribute__ ((constructor));

int _objc_rtClassDump(void) {
  int numClasses;
  int numMethods;
  int numProperties;
  int outFile;
  intptr_t methodImplementation;

  Class *classes = NULL;
  Method *methods = NULL;
  objc_property_t *properties = NULL;

  numClasses = objc_getClassList(NULL, 0);

  if (numClasses > 0)
  {
    classes = malloc(sizeof(Class) * numClasses);
    numClasses = objc_getClassList(classes, numClasses);

    outFile = open(OUTFILE_LOCATION, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    for (int i = 0; i < numClasses; i++) {
      dprintf(outFile, "%s\n", class_getName(classes[i]));

      objc_property_t *properties = class_copyPropertyList(classes[i], &numProperties);

      if (numProperties > 0) { dprintf(outFile, "  Properties\n"); }

      for (int i = 0; i < numProperties; i++) {
        dprintf(outFile, "    %s\n", property_getName(properties[i]));
      }

      free(properties);

      methods = class_copyMethodList(classes[i], &numMethods);

      if (numMethods > 0) { dprintf(outFile, "  Instance Methods\n"); }

      for (int i = 0; i < numMethods; i++) {
        methodImplementation = (intptr_t) method_getImplementation(methods[i]);
        dprintf(outFile, "    %s\t%#lx\n", sel_getName(method_getName(methods[i])), methodImplementation);
      }

      free(methods);

      methods = class_copyMethodList(object_getClass(classes[i]), &numMethods);

      if (numMethods > 0) { dprintf(outFile, "  Class Methods\n"); }

      for (int i = 0; i < numMethods; i++) {
        methodImplementation = (intptr_t) method_getImplementation(methods[i]);
        dprintf(outFile, "    %s\t%#lx\n", sel_getName(method_getName(methods[i])), methodImplementation);
      }

      free(methods);
    }

    close(outFile);
    free(classes);
  }

  return numClasses;
}