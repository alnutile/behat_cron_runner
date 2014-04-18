<?php namespace Drupal\BehatRunner\Events;

use BehatWrapper\Event\BehatOutputListenerInterface;
use BehatWrapper\Event\BehatOutputEvent;

/**
 * Interface implemented by output listeners.
 */
class BehatCronRunnerEventListener implements BehatOutputListenerInterface
{

    public $pids = array();
    public function __construct()
    {
        $this->pids = array();
    }
    public function handleOutput(BehatOutputEvent $event)
    {
        print "Event type {$event->getType()}";
        $pid = $event->getProcess()->getPid();
        if(!isset($this->pids[$pid])) {
            $this->pids[$pid]= 1;
        }
        if($event->isError()) {
            echo "Error error {$this->pids[$pid]}";
        } else {
            echo $event->getBuffer();
        }
    }
}
