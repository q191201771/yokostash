package main

import (
	"github.com/q191201771/naza/pkg/nazalog"
	"net/http"
	"runtime"
	"sync"
	"time"

	_ "net/http/pprof"
)


var mu sync.Mutex

func fn(n int) {
	time.Sleep(time.Duration(n) * time.Second)

		mu.Lock()
		mu.Unlock()
}

func main() {
	nazalog.Debugf("> main")

	go func() {
		s := &http.Server{Addr: ":12345", Handler: nil}
		s.ListenAndServe()
	}()

	runtime.SetMutexProfileFraction(1)

	go fn(2)
	go fn(3)

	mu.Lock()
	time.Sleep(11 * time.Second)
	mu.Unlock()

	nazalog.Debugf("end")


	time.Sleep(24 * time.Hour)
}