package main

import (
	"github.com/q191201771/naza/pkg/nazalog"
	"runtime"
	"time"
)

type A struct {

}

func Finalize(a *A) {
	nazalog.Debugf("> Finalize")
	runtime.SetFinalizer(a, Finalize)
	//a = nil

}

func main() {
	a := &A{}
	runtime.SetFinalizer(a, Finalize)
	a = nil

	for {
		nazalog.Debugf("> GC()")
		runtime.GC()
		time.Sleep(1 * time.Second)
	}
}
